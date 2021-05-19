#pragma once

#include "field.hpp"

class PointSourceForceField : public ForceField {
public:
    PointSourceForceField(double s);
    arma::vec2 f(Object *obj) const;
private:
    double s;
};