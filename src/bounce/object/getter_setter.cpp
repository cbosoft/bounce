#include <bounce/object/object.hpp>

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

void Object::set_position(const arma::vec2 &position)
{
    this->new_position = position;
    Transform::set_position(position);
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

void Object::set_fixed(bool value)
{
    this->_fixed = value;
}

const Colour &Object::get_colour() const
{
    return this->c;
}

void Object::set_colour(const Colour &colour)
{
    this->c = colour;
}

void Object::attach_renderable(const std::string &name, Renderable *renderable)
{
    renderable->set_object(this);
    Transform::attach_renderable(name, renderable);
}

void Object::attach_renderable(Renderable *rbl)
{
    rbl->set_object(this);
    Transform::attach_renderable(rbl);
}

const std::string &Object::get_layer() const
{
    return this->_layer;
}

void Object::set_layer(const std::string &layer)
{
    this->_layer = layer;
}

const CollisionShape &Object::get_shape() const
{
    return this->_shape;
}

void Object::set_shape(const CollisionShape &shape)
{
    this->_shape = shape;

    if (this->_renderable_collider) {
        delete this->_renderable_collider;
        this->_renderable_collider = nullptr;
    }

    switch (shape.get_type()) {
        case ST_CIRCLE:
            this->_renderable_collider = new RegularPolygonMeshRenderable(20);
            break;
        case ST_RECT:
            this->_renderable_collider = new RectangleMeshRenderable(1, 1);
            break;
    }

    this->_renderable_collider->set_border_size(0.5);
    this->_renderable_collider->set_colour(Colours::clear);
    this->_renderable_collider->set_border_colour(Colours::yellow);
    this->_renderable_collider->set_parent(this);
    this->_renderable_collider->set_z(1000);
}

void Object::set_bounciness(double bounciness)
{
    this->_material.bounciness = bounciness;
}

void Object::set_friction(double friction)
{
    this->_material.dynamic_friction = friction;
}

const PhysicsMaterial &Object::get_material() const
{
    return this->_material;
}