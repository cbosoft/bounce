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
    ~Object();

    void timestep(double dt);

    void accept_position();

    void set_mass(double mass);
    double get_mass() const;

    bool fixed() const;
    void set_fixed(bool value);

    const Colour &get_colour() const;
    void set_colour(const Colour &colour);

    const arma::vec2 &get_new_position() const;
    const arma::vec2 &get_velocity() const;
    const arma::vec2 &get_force() const;

    void set_relative_position(const arma::vec2 &position) override;
    void set_position(const arma::vec2 &position) override;
    void set_new_position(const arma::vec2 &new_position);
    void set_new_position(const arma::vec2 &&new_position);
    void set_velocity(const arma::vec2 &new_position);
    void set_velocity(const arma::vec2 &&new_position);
    void set_force(const arma::vec2 &force);
    void set_force(const arma::vec2 &&force);
    void add_force(const arma::vec2 &force);

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

    bool is_a(const std::string &s) const;

protected:
    void set_identifier(const std::string &s);

private:
    CollisionShape _shape;
    arma::vec2 new_position;
    arma::vec2 velocity;
    arma::vec2 force;

    double mass, inv_mass;
    std::string _layer;

    PhysicsMaterial _material;

    Colour c;

    bool _fixed;
    MeshRenderable *_renderable_collider;

    std::size_t _type_identifier;
};
