#include <bounce/physics/collider/collider.hpp>

void Collider::set_touching(CollisionDirection dir)
{
    unsigned int i = 1 << (unsigned int)dir;
    this->_touching_flags |= i;
}

void Collider::set_not_touching_anything()
{
    this->_touching_flags = 0;
}

void Collider::set_not_touching(CollisionDirection dir)
{
    unsigned int i = 1 << (unsigned int)dir;
    this->_touching_flags &= ~i;
}

bool Collider::is_touching(CollisionDirection dir) const
{
    unsigned int i = 1 << (unsigned int)dir;
    return this->_touching_flags & i;
}

bool Collider::is_touching_top() const { return this->is_touching(CD_TOP); }
bool Collider::is_touching_left() const { return this->is_touching(CD_LEFT); }
bool Collider::is_touching_bottom() const { return this->is_touching(CD_BOTTOM); }
bool Collider::is_touching_right() const { return this->is_touching(CD_RIGHT); }
