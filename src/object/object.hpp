#pragma once
#include <armadillo>
#include <vector>

#include "../shapes/shapes.hpp"


class PhysicsObject {
  public:
    PhysicsObject(arma::vec2 position, bool fixed=false);

    void timestep(double dt, double g);

    void accept_position();
    void add_geometry(GeometricEquation *eqn);
    void add_geometry(std::vector<GeometricEquation *> eqns);

    bool will_collide(const PhysicsObject *other, arma::vec2 &norm) const;
    bool fixed() const;

    arma::vec2 position;
    arma::vec2 new_position;
    arma::vec2 velocity;

  public:
    bool _fixed;
    std::vector<GeometricEquation *> eqns;
};
