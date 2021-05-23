#pragma once

#include "field.hpp"

class PointSourceForceField : public ForceField {
public:
    PointSourceForceField(double s);
    arma::vec2 f(Rigidbody *obj) const;
private:
    double s;
};