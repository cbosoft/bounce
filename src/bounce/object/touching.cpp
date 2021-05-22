#include <bounce/object/object.hpp>

void Object::set_touching(CollisionDirection dir)
{
    unsigned int i = 1 << (unsigned int)dir;
    this->_colliding_flags |= i;
}

void Object::set_not_touching_anything()
{
    this->_colliding_flags = 0;
}

void Object::set_not_touching(CollisionDirection dir)
{
    unsigned int i = 1 << (unsigned int)dir;
    this->_colliding_flags &= ~i;
}

bool Object::is_touching(CollisionDirection dir) const
{
    unsigned int i = 1 << (unsigned int)dir;
    return this->_colliding_flags & i;
}

bool Object::is_touching_top() const { return this->is_touching(CD_TOP); }
bool Object::is_touching_left() const { return this->is_touching(CD_LEFT); }
bool Object::is_touching_bottom() const { return this->is_touching(CD_BOTTOM); }
bool Object::is_touching_right() const { return this->is_touching(CD_RIGHT); }
