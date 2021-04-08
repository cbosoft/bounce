#include "point_source.hpp"

PointSourceForceField::PointSourceForceField(double s)
: s(s)
{
    // do nothing
}

arma::vec2 PointSourceForceField::f(const arma::vec2 &pt) const
{
    arma::vec dp = pt - this->get_position();
    double r = arma::dot(dp, dp);
    if (r == 0)
        return {0.0, 0.0};
    arma::vec2 dir = arma::normalise(dp);
    return dir*this->s*r;  ///r/r*9e5;
}