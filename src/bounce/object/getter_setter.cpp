#include <bounce/object/object.hpp>

void Object::set_mass(double mass)
{
    this->_mass = mass;
    this->_inv_mass = 1./mass;
}

double Object::get_mass() const
{
    return this->_mass;
}

void Object::set_velocity(const arma::vec2 &_velocity)
{
    this->_velocity = _velocity;
}

void Object::set_force(const arma::vec2 &_force)
{
    this->_force = _force;
}

const arma::vec2 &Object::get_velocity() const
{
    return this->_velocity;
}

const arma::vec2 &Object::get_force() const
{
    return this->_force;
}

void Object::add_force(const arma::vec2 &dforce)
{
    this->_force += dforce;
}

bool Object::fixed() const
{
    return this->_fixed;
}

void Object::set_fixed(bool value)
{
    this->_fixed = value;
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
        this->remove_child(this->_renderable_collider);
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