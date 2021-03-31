#include "game/game.hpp"
#include "physics/field/force_fields.hpp"
#include "shapes/shapes.hpp"

int main()
{
  Game game;
  auto &pe = PhysicsEngine::engine();
  pe.add_field(new UnboundedLinearForceField(0, 0, 0, -10));

  PhysicsObject *o = nullptr;

  o = new PhysicsObject({0, 0}, true);
  o->add_geometry(new Line(0.1, 0, -50, 50));
  game.add_object(o);

  o = new PhysicsObject({-50, 0}, true);
  o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{0, 50}));
  game.add_object(o);

  o = new PhysicsObject({ 50, 0}, true);
  o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{0, 50}));
  game.add_object(o);

  // ball
  o = new PhysicsObject({0, 10}, false);
  o->add_geometry(gen_circle(1.0));
  game.add_object(o);

  game.run();
  return 0;
}
