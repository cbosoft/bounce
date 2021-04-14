#include "renderable.hpp"
#include "../../object/object.hpp"

bool Renderable::is_fixed() const
{
    return this->_object == nullptr;
}

double Renderable::get_scale() const
{
    if (this->is_fixed()) {
        return this->_scale;
    }
    else {
        return this->_object->get_radius();
    }
}

void Renderable::set_scale(double scale)
{
    if (this->is_fixed()) {
        this->_scale = scale;
    }
    else {
        this->_object->set_radius(scale);
    }
}

void Renderable::set_object(Object *object)
{
    this->_object = object;
    this->set_parent(object);
}

Object *Renderable::get_object() const
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

const Colour &Renderable::get_colour() const
{
    if (this->is_fixed()) {
        return this->_colour;
    }
    else {
        return this->_object->get_colour();
    }
}

void Renderable::set_colour(const Colour &colour)
{
    if (this->is_fixed()) {
        this->_colour = colour;
    }
    else {
        this->_object->set_colour(colour);
    }
}
