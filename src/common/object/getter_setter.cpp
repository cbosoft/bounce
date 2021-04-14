#include "object.hpp"

void Object::set_mass(double _mass)
{
    this->mass = _mass;
    this->inv_mass = 1./_mass;
}

double Object::get_mass() const
{
    return this->mass;
}

void Object::set_new_position(const arma::vec2 &_new_position)
{
    this->new_position = _new_position;
}

void Object::set_new_position(const arma::vec2 &&_new_position)
{
    this->new_position = _new_position;
}

void Object::set_velocity(const arma::vec2 &_velocity)
{
    this->velocity = _velocity;
}

void Object::set_velocity(const arma::vec2 &&_velocity)
{
    this->velocity = _velocity;
}

void Object::set_force(const arma::vec2 &_force)
{
    this->force = _force;
}

void Object::set_force(const arma::vec2 &&_force)
{
    this->force = _force;
}

const arma::vec2 &Object::get_new_position() const
{
    return this->new_position;
}

const arma::vec2 &Object::get_velocity() const
{
    return this->velocity;
}

const arma::vec2 &Object::get_force() const
{
    return this->force;
}

void Object::add_force(const arma::vec2 &dforce)
{
    this->force += dforce;
}

bool Object::fixed() const
{
    return this->_fixed;
}


double Object::get_cor() const
{
    return this->cor;
}

void Object::set_cor(double _cor)
{
    this->cor = _cor;
}

double Object::get_radius() const
{
    return this->_radius;
}

void Object::set_radius(double radius)
{
    this->_radius = radius;
}

const Colour &Object::get_colour() const
{
    return this->c;
}

void Object::set_colour(const Colour &colour)
{
    this->c = colour;
}

Renderable *Object::get_renderable() const
{
    return this->_renderable;
}

void Object::set_renderable(Renderable *renderable)
{
    renderable->set_object(this);
    this->_renderable = renderable;
}

const std::string &Object::get_layer() const
{
    return this->_layer;
}

void Object::set_layer(const std::string &layer)
{
    this->_layer = layer;
}
