#pragma once
#include <armadillo>
#include <vector>

#include "../../transform/transform.hpp"
#include "../../colour/colour.hpp"
#include "../../renderer/renderable/renderable.hpp"

class PhysicsObject : public Transform {
  public:
    PhysicsObject(Transform *parent, const arma::vec2 &position, bool fixed=false, double cor=1.0);
    PhysicsObject(Transform *parent, const arma::vec2 &position, double mass, double cor=1.0);
    virtual ~PhysicsObject() =default;

    void timestep(double dt);

    void accept_position();

    void set_mass(double mass);
    double get_mass() const;

    bool fixed() const;

    const Colour &get_colour() const;
    void set_colour(const Colour &colour);

    const arma::vec2 &get_new_position() const;
    const arma::vec2 &get_velocity() const;
    const arma::vec2 &get_force() const;

    void set_new_position(const arma::vec2 &new_position);
    void set_new_position(const arma::vec2 &&new_position);
    void set_velocity(const arma::vec2 &new_position);
    void set_velocity(const arma::vec2 &&new_position);
    void set_force(const arma::vec2 &force);
    void set_force(const arma::vec2 &&force);

    double get_radius() const;
    void set_radius(double radius);

    bool will_collide_with(const PhysicsObject *other);
    bool will_collide_with(const PhysicsObject *other, arma::vec2 &normal);
    bool will_collide_with(const PhysicsObject *other, arma::vec2 &normal, arma::vec2 &at);

    double get_cor() const;
    void set_cor(double _cor);

    Renderable *get_renderable() const;
    void set_renderable(Renderable *renderable);

  private:
    arma::vec2 new_position;
    arma::vec2 velocity;
    arma::vec2 force;

    double mass, inv_mass, cor, _radius;
    static constexpr double COLLISION_THRESH = 1e-2;

    Colour c;

    bool _fixed;
    Renderable *_renderable;
};
