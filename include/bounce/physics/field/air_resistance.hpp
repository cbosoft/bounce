#pragma once

#include "field.hpp"

class AirResField : public ForceField {
public:
    [[nodiscard]] AirResField(double strength);

    arma::vec2 f(Object *obj) const override;

    void set_strength(double strength);

private:
    double _strength;
};