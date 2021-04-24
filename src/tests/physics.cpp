#include "../common/bounce.hpp"
#include <gtest/gtest.h>

TEST(PhysicsTest, PhysicsEngine_GravityField) {
    double mass = 1.0;
    Game &game = Game::ref();
    Scene *dummy = new Scene("dummy");
    game.add_scene(dummy);
    Object o(dummy, {0, 0}, mass);

    double force_due_to_gravity = -10;
    dummy->add_field(new UnboundedLinearForceField(0, 0, 0, force_due_to_gravity));

    PhysicsEngine &pe = PhysicsEngine::ref();
    pe.timestep_objects();

    arma::vec2 accel{0, force_due_to_gravity/mass};
    arma::vec2 vel = accel*pe.get_dt();

    arma::vec2 dv = o.get_velocity() - vel;
    EXPECT_DOUBLE_EQ(dv[0], 0.0);
    EXPECT_DOUBLE_EQ(dv[1], 0.0);
}

TEST(PhysicsTest, PhysicsEngine_MultipleFields) {
    double mass = 1.0;
    Game &game = Game::ref();
    Scene *dummy = new Scene{"dummy"};
    game.add_scene(dummy);
    Object o(dummy, {0, 0}, mass);

    double force_due_to_gravity = -10;
    dummy->add_field(new UnboundedLinearForceField(0, 0, 0, force_due_to_gravity));
    dummy->add_field(new UnboundedLinearForceField(0, 0, 0, -force_due_to_gravity));
    dummy->add_field(new UnboundedLinearForceField(0, force_due_to_gravity, 0, 0));
    dummy->add_field(new UnboundedLinearForceField(0, -force_due_to_gravity, 0, 0));

    PhysicsEngine &pe = PhysicsEngine::ref();
    pe.timestep_objects();

    EXPECT_DOUBLE_EQ(o.get_velocity()[0], 0.0);
    EXPECT_DOUBLE_EQ(o.get_velocity()[1], 0.0);
}
