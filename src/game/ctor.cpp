#include "game.hpp"

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
