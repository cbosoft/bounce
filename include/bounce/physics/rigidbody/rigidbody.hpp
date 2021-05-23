#pragma once

#include "../collider/collider.hpp"
#include "../material/material.hpp"

class Rigidbody : public Collider {
public:
    explicit Rigidbody(Transform *parent);
    explicit Rigidbody(json j);

    void timestep_force(double dt);
    void timestep_velocity(double dt);

    void set_mass(double mass);
    [[nodiscard]] double get_mass() const;

    [[nodiscard]] bool is_fixed() const;
    void set_fixed(bool value);

    void set_velocity(const arma::vec2 &velocity);
    [[nodiscard]] const arma::vec2 &get_velocity() const;

    void set_force(const arma::vec2 &force);
    void add_force(const arma::vec2 &force);
    [[nodiscard]] const arma::vec2 &get_force() const;

    [[nodiscard]] const PhysicsMaterial &get_material() const;
    void set_bounciness(double bounciness);
    void set_friction(double friction);

    virtual void on_physics_update() {}

    json serialise() override;

protected:
    arma::vec2 _velocity, _previous_velocity, _force;
    double _mass, _inv_mass;
    PhysicsMaterial _material;
    bool _fixed;
};