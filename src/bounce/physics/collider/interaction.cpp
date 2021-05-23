#include <bounce/physics/collider/collider.hpp>

void Collider::set_interaction_mask(unsigned int mask)
{
    this->_interaction_mask = mask;
}

bool Collider::can_interact() const
{
    return this->_interaction_mask;
}

unsigned int Collider::get_interaction_mask() const
{
    return this->_interaction_mask;
}

bool Collider::does_interact_with(const Collider *other) const
{
    return this->does_interact_with(other->_interaction_mask);
}

bool Collider::does_interact_with(unsigned int mask) const
{
    return this->_interaction_mask & mask;
}
