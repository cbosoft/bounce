#pragma once
#include "../../transform/transform.hpp"

class ForceField: public Transform {
public:
    virtual ~ForceField() = default;

    virtual arma::vec2 measure_at(const arma::vec2 &p) const;
    virtual arma::vec2 f(const arma::vec2 &p) const =0;
};