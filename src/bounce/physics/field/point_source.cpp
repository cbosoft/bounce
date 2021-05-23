#include <bounce/physics/field/point_source.hpp>

PointSourceForceField::PointSourceForceField(double s)
: s(s)
{
    // do nothing
}

arma::vec2 PointSourceForceField::f(Rigidbody *obj) const
{
    arma::vec dp = obj->get_position() - this->get_position();
    double r = arma::dot(dp, dp);
    if (r == 0)
        return {0.0, 0.0};
    arma::vec2 dir = arma::normalise(dp);
    return dir*this->s/r/r*9e5;
}