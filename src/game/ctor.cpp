#include "game.hpp"

Game::Game(int w, int h)
  : w(w)
  , h(h)
  , should_quit(false)
  , win(nullptr)
  , renderer(nullptr)
{
  // OBJECTS INIT
  auto *po = new PhysicsObject({0, 10}, false);
  po->add_geometry(gen_circle(1));
  this->add_object(po);

  po = new PhysicsObject({0, 0}, true);
  po->add_geometry(new Line(-0.5, 0, -100, 100));
  this->add_object(po);

  po = new PhysicsObject({0, -15}, true);
  po->add_geometry(new Line(1, 0, -100, 100));
  this->add_object(po);

  this->render_init();
}
