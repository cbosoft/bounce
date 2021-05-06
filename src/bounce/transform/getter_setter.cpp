#include <bounce/transform/transform.hpp>

Transform * Transform::get_parent() const
{
    return this->_parent;
}

const Transform *Transform::get_root() const
{
    if (this->_parent) {
        return this->_parent->get_root();
    }
    return this;
}

void Transform::remove_child(Transform *child)
{
    this->_children.remove(child);
}

void Transform::add_child(Transform *child)
{
    this->_children.push_back(child);
}

const std::list<Transform *> &Transform::get_children() const
{
    return this->_children;
}

void Transform::set_parent(Transform *parent)
{
    if (this->_parent) {
        this->_parent->remove_child(this);
    }
    this->_parent = parent;
    this->_parent->add_child(this);
}

arma::vec2 Transform::get_relative_position() const
{
    return this->_relative_position*this->get_scale();
}

void Transform::set_relative_position(const arma::vec2 &relative_position)
{
    this->_relative_position = relative_position;
}

arma::vec2 Transform::get_position() const
{
    arma::vec2 rv = this->get_relative_position();
    if (this->_parent)
        rv += this->_parent->get_position();
    return rv;
}

void Transform::set_position(const arma::vec2 &position)
{
    arma::vec2 relpos = position;
    if (this->_parent)
        relpos -= this->_parent->get_position();
    this->set_relative_position(relpos);
}

unsigned long Transform::count() const
{
    unsigned long rv = 1;
    for (const Transform *child : this->_children)
        rv += child->count();
    return rv;
}

void Transform::activate()
{
    this->_active = true;
    this->on_activate();
    for (Transform *child : this->_children)
        child->activate();
}

void Transform::deactivate()
{
    this->_active = false;
    this->on_deactivate();
    for (Transform *child : this->_children)
        child->deactivate();
}

bool Transform::is_active() const
{
    return this->_active;
}

void Transform::set_scale(double scale)
{
    this->_scale = scale;
}

double Transform::get_scale() const
{
    double scale = this->_scale;
    if (_parent)
        scale *= this->_parent->get_scale();
    return scale;
}
