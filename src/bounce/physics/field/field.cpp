#include <bounce/physics/field/field.hpp>

arma::vec2 ForceField::measure_at(const arma::vec2 &p) const
{
    return this->f(p);
}