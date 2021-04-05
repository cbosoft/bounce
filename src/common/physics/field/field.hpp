#pragma once
#include <armadillo>

class ForceField {
public:
    virtual ~ForceField() = default;

    virtual arma::vec2 measure_at(const arma::vec2 &p) const;
    virtual arma::vec2 f(const arma::vec2 &p) const =0;
};