#include <bounce/object/object.hpp>

/**
 * Accept the provisional position for the Object.
 */
void Object::accept_position()
{
    this->set_position(this->new_position);
}