#pragma once

#include "../../transform/transform.hpp"
#include "../../object/object.hpp"

class ForceField: public Transform {
public:
    virtual ~ForceField() = default;

    virtual arma::vec2 measure_at(Object *obj) const;
    virtual arma::vec2 f(Object *obj) const =0;
};