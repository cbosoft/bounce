#include "../common/game/game.hpp"
#include "../common/physics/field/force_fields.hpp"
#include "../common/renderer/renderables.hpp"
#include "../version.hpp"

int main()
{
    std::cerr << GitMetadata::version_string() << std::endl;
    auto &pe = PhysicsEngine::init_engine(1e-3, 1.0);
    (void)pe;
    Game game;

    PhysicsObject *o = nullptr;
    Transform root;

    // platform
    ForceField *f = new PointSourceForceField(-0.1);
    o = new PhysicsObject(&root, {0, 0}, true);
    o->set_radius(10.0);
    f->set_parent(o);
    game.add_object(o);
    pe.add_field(f);
    o->set_renderable(new CircleRenderable());
    o->set_colour(Colour::from_rgb_f(0.3, 0.3, 0.4));

    // double wrad = 1000, off=45;
    // walls
    // o = new PhysicsObject(&root, {-wrad-off, wrad}, true);
    // o->set_radius(wrad);
    // game.add_object(o);

    // o = new PhysicsObject(&root, { wrad+off, wrad}, true);
    // o->set_radius(wrad);
    // game.add_object(o);
    // o = new PhysicsObject(&root, { wrad+off, 0}, true);
    // o->set_radius(wrad);
    // game.add_object(o);
    // o = new PhysicsObject(&root, {-wrad-off, 0}, true);
    // o->set_radius(wrad);
    // game.add_object(o);

    // floor
    // o = new PhysicsObject(&root, {-wrad-off,-wrad-off}, true);
    // o->set_radius(wrad);
    // game.add_object(o);

    // o = new PhysicsObject(&root, { 0,-wrad-off}, true);
    // o->set_radius(wrad);
    // game.add_object(o);

    // o = new PhysicsObject(&root, { wrad+off,-wrad-off}, true);
    // o->set_radius(wrad);
    // game.add_object(o);

    // balls
    // o = new PhysicsObject(&root, {0, 10}, false, 1.0);
    // game.add_object(o);

    // f = new PointSourceForceField(-0.1);
    // o = new PhysicsObject(&root, {1, 20}, false, 1.0);
    // o->set_velocity({-10, 0});
    // f->set_parent(o);
    // game.add_object(o);
    // pe.add_field(f);

    // o = new PhysicsObject(&root, {-2, 30}, false, 1.0);
    // game.add_object(o);

    // f = new PointSourceForceField(-0.1);
    o = new PhysicsObject(&root, {30, 0}, false, 0.5);
    // o->set_radius(0.5);
    o->set_velocity({0.0, -45});
    // f->set_parent(o);
    game.add_object(o);
    // pe.add_field(f);
    o->set_renderable(new CircleRenderable());

    game.run();
    return 0;
}
