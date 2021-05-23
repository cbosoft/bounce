#include <bounce/physics/field/field.hpp>

arma::vec2 ForceField::measure_at(Rigidbody *obj) const
{
    return this->f(obj);
}