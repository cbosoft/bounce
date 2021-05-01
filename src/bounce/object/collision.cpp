#include <bounce/object/object.hpp>

/**
 * Accept the provisional position for the Object.
 */
void Object::accept_position()
{
    if (!this->fixed())
        this->set_position(this->new_position);
}