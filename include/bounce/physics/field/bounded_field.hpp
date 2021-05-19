#pragma once

#include "field.hpp"

class BoundedForceField : public virtual ForceField {
public:
    BoundedForceField(const arma::vec2 &topleft,
                      const arma::vec2 &bottomright);

    arma::vec2 measure_at(Object *obj) const override;

private:
    arma::vec2 topleft, bottomright;

    bool is_in_range(const arma::vec2 &p) const;

};