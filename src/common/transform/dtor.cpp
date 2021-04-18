#include "transform.hpp"

Transform::~Transform()
{
    if (this->_parent)
        this->_parent->remove_child(this);

    this->_named_renderables.clear();
    this->_anonymous_renderables.clear();

    std::list<Transform *> children_copy = this->_children;
    for (auto *child : children_copy) {
        delete child;
    }
}