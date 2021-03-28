#include "game.hpp"

Game::Game(double dt, double g, int w, int h)
  : w(w)
  , h(h)
  , dt(dt)
  , g(g)
  , irl_time(0)
  , physics_time(0)
  , should_quit(false)
  , win(nullptr)
  , renderer(nullptr)
{
  // OBJECTS INIT
  auto *po = new PhysicsObject({0, 0}, true);
  po->add_geometry(new Line(-0.5, 0, -100, 100));
  this->objects.push_back(po);

  po = new PhysicsObject({0, 4}, false);
  po->add_geometry(gen_circle(1));
  this->objects.push_back(po);

  this->render_init();
  this->physics_init();
}
