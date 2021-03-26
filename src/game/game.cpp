#include <SDL2/SDL.h>
#include <stdexcept>

#include "game.hpp"
#include "../shapes/shapes.hpp"

Game::Game(double dt, double g)
  : dt(dt)
  , g(g)
  , time(0)
  , should_quit(false)
  , win(nullptr)
  , renderer(nullptr)
{
  // OBJECTS INIT
  auto *po = new PhysicsObject({0, 0}, true);
  po->add_geometry(new Line(-0.5, 0, -100, 100));
  this->objects.push_back(po);

  po = new PhysicsObject({0, 10}, false);
  po->add_geometry(gen_circle(1));
  this->objects.push_back(po);

  // RENDERER INIT
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    throw std::runtime_error(SDL_GetError());
  }

  if (SDL_CreateWindowAndRenderer(640, 480, 0, &this->win, &this->renderer)) {
    throw std::runtime_error(SDL_GetError());
  }
}

Game::~Game()
{
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->win);
}

void Game::step()
{
  this->physics_step();
  this->render_step();
  this->input_step();
}

void Game::physics_step()
{
  this->time += this->dt;
  for (auto *obj : this->objects) {
    obj->timestep(this->dt, this->g);
  }

  for (size_t i = 0; i < this->objects.size(); i++) {
    for (size_t j = 0; j < this->objects.size(); j++) {
      if (j >= i) break;

      auto *o1 = this->objects[i], *o2 = this->objects[j];

      arma::vec2 norm;
      if (o1->will_collide(o2, norm)) {
        if (o1->fixed() || o2->fixed()) {
          auto *free_body = (o2->fixed()?o1:o2);
          double m = (o2->fixed()?1.0:-1.0);
          double vmag = arma::norm(free_body->velocity);
          free_body->velocity = norm * vmag * m;
          free_body->new_position = free_body->velocity*dt + free_body->position;
        }
        else {
          // TODO
        }
      }
    }
  }

  for (auto *obj : this->objects) {
    obj->accept_position();
  }
}

void Game::render_step()
{
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(this->renderer);
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(this->renderer, 320, 200, 300, 240);
  SDL_RenderPresent(this->renderer);
}

void Game::input_step()
{

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        this->should_quit = true;
        break;

      case SDL_KEYDOWN:
        this->keydown(e.key.keysym.scancode);
        break;
    }
  }

}

void Game::keydown(SDL_Scancode scancode)
{
  switch (scancode)
  {
    case SDL_SCANCODE_ESCAPE:
      this->should_quit = true;
      break;

    default:
      break;
  }
}

void Game::run()
{
  while (!this->should_quit)
  {
    this->step();
  }
}
