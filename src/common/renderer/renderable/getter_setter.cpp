#include "renderable.hpp"

bool Renderable::is_fixed() const
{
    return this->_object == nullptr;
}

double Renderable::get_x() const
{
    return this->x;
}

double Renderable::get_y() const
{
    return this->y;
}

double Renderable::get_scale() const
{
    return this->s;
}

void Renderable::set_scale(double v)
{
    this->s = v;
}

void Renderable::set_x(double v)
{
    this->x = v;
}

void Renderable::set_y(double v)
{
    this->y = v;
}

void Renderable::set_object(PhysicsObject *object)
{
    this->_object = object;
}

PhysicsObject *Renderable::get_object() const
{
    return this->_object;
}

bool Renderable::has_texture() const
{
    return !this->texture_name.empty();
}

const std::string &Renderable::get_texture_name() const
{
    return this->texture_name;
}

void Renderable::set_texture_name(const std::string &name)
{
    this->texture_name = name;
}
