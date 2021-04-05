#include "../common/physics/engine/engine.hpp"
#include "../common/physics/field/force_fields.hpp"
#include <gtest/gtest.h>

TEST(PhysicsTest, PhysicsEngine_GravityField) {
    double mass = 1.0;
    PhysicsObject o({0, 0}, mass);
    PhysicsEngine &pe = PhysicsEngine::init_engine(1e-4, 1.0);
    pe.add_object(&o);

    double force_due_to_gravity = -10;
    pe.add_field(new UnboundedLinearForceField(0, 0, 0, force_due_to_gravity));
    pe.timestep_objects();

    arma::vec2 accel{0, force_due_to_gravity/mass};
    arma::vec2 vel = accel*pe.get_dt();

    arma::vec2 dv = vel - o.get_velocity();
    EXPECT_DOUBLE_EQ(dv[0], 0.0);
    EXPECT_DOUBLE_EQ(dv[1], 0.0);
}

TEST(PhysicsTest, PhysicsEngine_MultipleFields) {
    double mass = 1.0;
    PhysicsObject o({0, 0}, mass);
    PhysicsEngine &pe = PhysicsEngine::init_engine(1e-4, 1.0);
    pe.add_object(&o);

    double force_due_to_gravity = -10;
    pe.add_field(new UnboundedLinearForceField(0, 0, 0, force_due_to_gravity));
    pe.add_field(new UnboundedLinearForceField(0, 0, 0, -force_due_to_gravity));
    pe.add_field(new UnboundedLinearForceField(0, force_due_to_gravity, 0, 0));
    pe.add_field(new UnboundedLinearForceField(0, -force_due_to_gravity, 0, 0));
    pe.timestep_objects();

    EXPECT_DOUBLE_EQ(o.get_velocity()[0], 0.0);
    EXPECT_DOUBLE_EQ(o.get_velocity()[1], 0.0);
}