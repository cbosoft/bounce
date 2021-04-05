#include "bounded_field.hpp"

BoundedForceField::BoundedForceField(const arma::vec2 &topleft, const arma::vec2 &bottomright)
: topleft(topleft)
, bottomright(bottomright)
{
    // do nothing
}

arma::vec2 BoundedForceField::measure_at(const arma::vec2 &p) const
{
    if (this->is_in_range(p))
        return this->f(p);

    return arma::vec2{0.0, 0.0};
}

bool BoundedForceField::is_in_range(const arma::vec2 &p) const
{
    bool x_in_range = ((this->topleft[0] <= p[0]) && (this->bottomright[0] <= p[0]));
    bool y_in_range = ((this->topleft[1] <= p[1]) && (this->bottomright[1] <= p[1]));
    return x_in_range && y_in_range;
}