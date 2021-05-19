#include <bounce/physics/field/field.hpp>

arma::vec2 ForceField::measure_at(Object *obj) const
{
    return this->f(obj);
}