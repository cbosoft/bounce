#include "game.hpp"

void Game::render_init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    throw std::runtime_error(SDL_GetError());
  }

  this->aspect_ratio = double(this->w)/double(this->h);
  this->camera_position = arma::vec2{-5, -50};
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
  pt = pt - this->camera_position;
  pt = pt % this->window_size / this->camera_size;
  pt = pt + this->window_size*0.5;
  pt[1] = this->h - pt[1];
  return pt;
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

  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(this->renderer);
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  for (auto *obj : this->objects) {

    auto pos = this->world_pt_to_screen_pt(obj->get_position());
    if (pos[0] < 0 || pos[1] > this->window_size[0] ||
        pos[1] < 0 || pos[1] > this->window_size[1]) {
      continue;
    }

    for (auto *eqn : obj->get_equations()) {
      auto points = eqn->as_points();
      int npoints = points.size();
      for (int i = 0; i < npoints - 1; i++) {
        auto point = this->world_pt_to_screen_pt(points[i]);
        auto next = this->world_pt_to_screen_pt(points[i+1]);

        if (point.has_nan() || next.has_nan())
          continue;

        int x1 = int(point[0]);
        int y1 = int(point[1]);
        int x2 = int(next[0]);
        int y2 = int(next[1]);

        if ((x1 < 0) || (x1 > this->w) ||
            (x2 < 0) || (x2 > this->w) ||
            (y1 < 0) || (y1 > this->h) ||
            (y2 < 0) || (y2 > this->h))
          continue;
        SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2);
      }
    }

  }

  SDL_RenderPresent(this->renderer);

}
