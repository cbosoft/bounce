#pragma once
#include <armadillo>
#include <vector>

#include "../../shapes/shapes.hpp"


class PhysicsObject {
  public:
    PhysicsObject(arma::vec2 position, bool fixed=false);
    PhysicsObject(arma::vec2 position, double mass);

    void timestep(double dt);

    void accept_position();
    void add_geometry(GeometricEquation *eqn);
    void add_geometry(std::vector<GeometricEquation *> eqns);

    void set_mass(double mass);

    bool will_collide(const PhysicsObject *other, arma::vec2 &norm) const;
    bool fixed() const;

    arma::vec2 position;
    arma::vec2 new_position;
    arma::vec2 velocity;
    arma::vec2 force;
    std::vector<GeometricEquation *> eqns;

  private:
    double mass, inv_mass;
    bool _fixed;
};
