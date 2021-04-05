#include "../common/game/game.hpp"
#include "../common/physics/field/force_fields.hpp"
#include "../version.hpp"

int main()
{
    std::cerr << GitMetadata::version_string() << std::endl;
    Game game;
    auto &pe = PhysicsEngine::init_engine(1e-3, 2.0);
    pe.add_field(new UnboundedLinearForceField(0, 0, 0, -10));

    PhysicsObject *o = nullptr;
    Transform root;

    // platform
    o = new PhysicsObject(&root, {0, 0}, true);
    game.add_object(o);

    auto cam = game.get_camera();
    cam.set_parent(o);

    double wrad = 1000, off=45;
    // walls
    o = new PhysicsObject(&root, {-wrad-off, wrad}, true);
    o->set_radius(wrad);
    game.add_object(o);

    o = new PhysicsObject(&root, { wrad+off, wrad}, true);
    o->set_radius(wrad);
    game.add_object(o);
    o = new PhysicsObject(&root, { wrad+off, 0}, true);
    o->set_radius(wrad);
    game.add_object(o);
    o = new PhysicsObject(&root, {-wrad-off, 0}, true);
    o->set_radius(wrad);
    game.add_object(o);

    // floor
    o = new PhysicsObject(&root, {-wrad-off,-wrad-off}, true);
    o->set_radius(wrad);
    game.add_object(o);

    o = new PhysicsObject(&root, { 0,-wrad-off}, true);
    o->set_radius(wrad);
    game.add_object(o);

    o = new PhysicsObject(&root, { wrad+off,-wrad-off}, true);
    o->set_radius(wrad);
    game.add_object(o);

    // balls
    o = new PhysicsObject(&root, {0, 10}, false, 1.0);
    game.add_object(o);

    o = new PhysicsObject(&root, {1, 20}, false, 1.0);
    game.add_object(o);

    o = new PhysicsObject(&root, {-2, 30}, false, 1.0);
    game.add_object(o);

    o = new PhysicsObject(&root, {4, 40}, false, 1.0);
    game.add_object(o);

    game.run();
    return 0;
}
