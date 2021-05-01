#pragma once

#include "field.hpp"

class PointSourceForceField : public ForceField {
public:
    PointSourceForceField(double s);
    arma::vec2 f(const arma::vec2 &pt) const;
private:
    double s;
};