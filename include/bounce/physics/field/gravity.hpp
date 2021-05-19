#pragma once

#include "field.hpp"

class GravityField : public ForceField {
public:
    [[nodiscard]] GravityField(double strength);

    arma::vec2 f(Object *obj) const override;

    void set_strength(double strength);

protected:
    double _strength;
};

