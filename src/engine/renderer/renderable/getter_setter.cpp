#include "renderable.hpp"
#include "../renderer.hpp"
#include "../../object/object.hpp"

bool Renderable::is_fixed() const
{
    return this->_object == nullptr;
}

void Renderable::set_size(const arma::vec2 &size)
{
    this->_size = size;
}

const arma::vec2 &Renderable::get_size() const
{
    return this->_size;
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
    return !this->_texture->is_null();
}

Texture *Renderable::get_texture() const
{
    return this->_texture;
}

void Renderable::set_texture_name(const std::string &name)
{
    this->_texture = Renderer::get().get_texture(name);
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

const Colour &Renderable::get_border_colour() const
{
    return this->_border_colour;
}

void Renderable::set_border_colour(const Colour &colour)
{
    this->_border_colour = colour;
}

double Renderable::get_border_size() const
{
    return this->_border_size;
}

void Renderable::set_border_size(double border_size)
{
    this->_border_size = border_size;
}

void Renderable::set_z(int z)
{
    this->_z = z;
}

int Renderable::get_z() const
{
    return this->_z;
}

void Renderable::set_visible(bool visibility)
{
    this->_visible = visibility;
}

bool Renderable::get_visible() const
{
    return this->_visible;
}

void Renderable::hide()
{
    this->set_visible(false);
}

void Renderable::show()
{
    this->set_visible(true);
}

void Renderable::set_shader_name(const std::string &name)
{
    this->_shader_name = name;
}

const std::string &Renderable::get_shader_name() const
{
    return this->_shader_name;
}

double Renderable::get_angle() const
{
    return this->_angle;
}

void Renderable::set_angle(double angle)
{
    this->_angle = angle;
}