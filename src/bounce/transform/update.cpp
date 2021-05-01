#include <bounce/transform/transform.hpp>

void Transform::update()
{
    this->on_update();
    for (auto *child : this->_children) {
        child->update();
    }
}