#include "transform.hpp"

Transform * Transform::get_parent() const
{
    return this->_parent;
}

void Transform::set_parent(Transform *parent)
{
    this->_parent = parent;
}

const arma::vec2 & Transform::get_relative_position() const
{
    return this->_relative_position;
}

void Transform::set_relative_position(const arma::vec2 &relative_position)
{
    this->_relative_position = relative_position;
}

arma::vec2 Transform::get_position() const
{
    auto rv = this->get_relative_position();
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


