#include "unbounded_linear.hpp"

UnboundedLinearForceField::UnboundedLinearForceField(double mx, double cx, double my, double cy)
: mx(mx)
, cx(cx)
, my(my)
, cy(cy)
{
    // do nothing
}

arma::vec2 UnboundedLinearForceField::f(const arma::vec2 &p) const
{
    double fx = this->mx*p[0] + this->cx;
    double fy = this->my*p[1] + this->cy;
    return arma::vec2{fx, fy};
}