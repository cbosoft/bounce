#pragma once

#include "../rigidbody/rigidbody.hpp"
#include "../../transform/transform.hpp"

class ForceField: public Transform {
public:
    virtual ~ForceField() = default;

    virtual arma::vec2 measure_at(Rigidbody *obj) const;
    virtual arma::vec2 f(Rigidbody *obj) const =0;
};