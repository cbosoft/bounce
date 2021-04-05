#pragma once

#include "../shapes/shapes.hpp"
#include "../transform/transform.hpp"

class Renderable : public Transform {
public:
    explicit Renderable(Transform *parent);
    Renderable(Transform *parent, GeometricEquation *shape);
    Renderable(Transform *parent, const std::vector<GeometricEquation *> &shape);

    void add_geometry(GeometricEquation *eqn);
    void add_geometry(const std::vector<GeometricEquation *> &eqns);
    std::vector<GeometricEquation *> get_shape() const;
    std::vector<std::vector<arma::vec2>> get_lines();

    virtual bool cache_invalid() const;

private:
    std::vector<std::vector<arma::vec2>> _cached_lines;
    std::vector<GeometricEquation *> _shape;
};