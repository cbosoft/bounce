#include "game/game.hpp"
#include "physics/field/force_fields.hpp"
#include "shapes/shapes.hpp"

int main()
{
    Game game;
    auto &pe = PhysicsEngine::init_engine(5e-4, 1.0);
    pe.add_field(new UnboundedLinearForceField(0, 0, 0, -10));

    PhysicsObject *o = nullptr;
    Transform root;

    // platform
    o = new PhysicsObject(&root, {0, 0}, true);
    o->add_geometry(new Line(3, 0, -5, 5));
    game.add_object(o);

    auto cam = game.get_camera();
    cam.set_parent(o);

    // walls
    o = new PhysicsObject(&root, {-50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{0, 50}));
    game.add_object(o);

    o = new PhysicsObject(&root, { 50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{0, 50}));
    game.add_object(o);

    // floor
    o = new PhysicsObject(&root, {-50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{50, -25}));
    game.add_object(o);

    o = new PhysicsObject(&root, { 50, 0}, true);
    o->add_geometry(Line::from_points(arma::vec2{0, 0}, arma::vec2{-50, -25}));
    game.add_object(o);

    // balls
    o = new PhysicsObject(&root, {0, 10}, false, 1.0);
    o->add_geometry(gen_circle(1.0));
    game.add_object(o);

    o = new PhysicsObject(&root, {1, 20}, false, 1.0);
    o->add_geometry(gen_circle(1.0));
    game.add_object(o);

    o = new PhysicsObject(&root, {-2, 30}, false, 1.0);
    o->add_geometry(gen_circle(1.0));
    game.add_object(o);

    o = new PhysicsObject(&root, {4, 40}, false, 1.0);
    o->add_geometry(gen_regular_polygon(2.0, 4));
    game.add_object(o);

    game.run();
    return 0;
}
