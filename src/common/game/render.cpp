#include "game.hpp"
#include "../colour/colour.hpp"

void Game::render_init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    throw std::runtime_error(SDL_GetError());
  }

  this->aspect_ratio = double(this->w)/double(this->h);
  this->set_camera_size(100);
  this->window_size = arma::vec2{double(this->w), double(this->h)};
  if (SDL_CreateWindowAndRenderer(this->w, this->h, 0, &this->win, &this->renderer)) {
    throw std::runtime_error(SDL_GetError());
  }

  this->time_of_last_render = Clock::now();
}

void Game::set_camera_size(double size)
{
  this->camera_size = arma::vec2{size*this->aspect_ratio, size};
}

arma::vec2 Game::world_pt_to_screen_pt(arma::vec2 pt)
{
  pt = pt - this->camera_transform.get_position();
  pt = pt % this->window_size / this->camera_size;
  pt = pt + this->window_size*0.5;
  pt[1] = this->h - pt[1];
  return pt;
}

double Game::world_len_to_screen_len(double l)
{
    return l * this->window_size[0] / this->camera_size[0];
}

// from: https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
// static void draw_circle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
// {
//     const int32_t diameter = (radius * 2);
//
//     int32_t x = (radius - 1);
//     int32_t y = 0;
//     int32_t tx = 1;
//     int32_t ty = 1;
//     int32_t error = (tx - diameter);
//
//     while (x >= y)
//     {
//         //  Each of the following renders an octant of the circle
//         SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
//         SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
//         SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
//         SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
//         SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
//         SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
//         SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
//         SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
//
//         if (error <= 0)
//         {
//             ++y;
//             error += ty;
//             ty += 2;
//         }
//
//         if (error > 0)
//         {
//             --x;
//             tx += 2;
//             error += (tx - diameter);
//         }
//     }
// }

static void draw_filled_circle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawLine(renderer, centreX + x, centreY - y, centreX + x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX - x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX + y, centreY - x, centreX + y, centreY + x);
        SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}





void Game::render_step()
{
    Clock::time_point now = Clock::now();
    Duration time_per_frame = now - this->time_of_last_render;
    double fps = 1./time_per_frame.count();

    if (fps > 60) {
        return;
    }

    this->time_of_last_render = now;

    Colour c = Colour::from_rgb(0, 0, 25);
    SDL_SetRenderDrawColor(this->renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->renderer);

    for (auto *obj : this->objects) {
        const Colour &c = obj->get_colour();
        SDL_SetRenderDrawColor(this->renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
        auto pos = this->world_pt_to_screen_pt(obj->get_position());

        int x = pos[0], y = pos[1], r = int(this->world_len_to_screen_len(obj->get_radius()));
        draw_filled_circle(this->renderer, x, y, r);

    }

    SDL_RenderPresent(this->renderer);

}
