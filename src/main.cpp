#include "game/game.hpp"
#include "physics/field/force_fields.hpp"
#include "shapes/shapes.hpp"

int main()
{
    Game game;
    auto &pe = PhysicsEngine::init_engine(1e-4, 1.0);
    pe.add_field(new UnboundedLinearForceField(0, 0, 0, -10));

    PhysicsObject *o = nullptr;

    // platform
    o = new PhysicsObject({0, 0}, true);
    o->add_geometry(new Line(1, 0, -5, 5));
    game.add_object(o);

    // walls
    o = new PhysicsObject({-50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{0, 50}));
    game.add_object(o);

    o = new PhysicsObject({ 50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{0, 50}));
    game.add_object(o);

    // floor
    o = new PhysicsObject({-50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{50, -25}));
    game.add_object(o);

    o = new PhysicsObject({ 50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{-50, -25}));
    game.add_object(o);

    // balls
    o = new PhysicsObject({0, 10}, false);
    o->add_geometry(gen_circle(1.0));
    game.add_object(o);

    o = new PhysicsObject({1, 20}, false);
    o->add_geometry(gen_circle(1.0));
    game.add_object(o);

    o = new PhysicsObject({-1, 30}, false);
    o->add_geometry(gen_circle(1.0));
    game.add_object(o);

    game.run();
    return 0;
}
