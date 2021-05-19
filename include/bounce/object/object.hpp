#pragma once
#include <armadillo>
#include <vector>

#include "../transform/transform.hpp"
#include "../colour/colour.hpp"
#include "../renderer/renderables.hpp"
#include "../physics/shape/shape.hpp"
#include "../physics/material/material.hpp"

class Object : public Transform {
  public:
    explicit Object(Transform *parent);
    explicit Object(json j);
    ~Object();

    void timestep_force(double dt);
    void timestep_velocity(double dt);

    void set_mass(double mass);
    double get_mass() const;

    bool fixed() const;
    void set_fixed(bool value);

    void set_velocity(const arma::vec2 &velocity);
    const arma::vec2 &get_velocity() const;

    void set_force(const arma::vec2 &force);
    void add_force(const arma::vec2 &force);
    const arma::vec2 &get_force() const;

    const PhysicsMaterial &get_material() const;
    void set_bounciness(double bounciness);
    void set_friction(double friction);

    void set_layer(const std::string &layer);
    const std::string &get_layer() const;

    virtual void on_physics_update() {}
    virtual void on_collision(Object *other) {}

    [[nodiscard]] bool is_physics_object() const override { return true; }
    void get_renderables(std::list<const Renderable *> &out) const override;

    [[nodiscard]] const CollisionShape &get_shape() const;
    void set_shape(const CollisionShape &shape);

    json serialise() override;

private:
    CollisionShape _shape;
    arma::vec2 _velocity, _previous_velocity, _force;

    double _mass, _inv_mass;
    std::string _layer;

    PhysicsMaterial _material;

    bool _fixed;
    MeshRenderable *_renderable_collider;
};
