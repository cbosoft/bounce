#include <bounce/object/object.hpp>

Object::Object(json j)
:   Transform(j)
,   _shape(CollisionShape(j["shape"]))
,   new_position({0, 0})
,   velocity({0, 0})
,   force({0, 0})
,   mass(1.0)
,   inv_mass(1.0)
,   _layer("unset")
,   _material({1.0, 0.0})
,   _fixed(false)
,   _renderable_collider(nullptr)
{
    this->velocity = jsonvec2(j["velocity"]);
    this->force = jsonvec2(j["force"]);
    this->set_mass(j["mass"]);
    this->_layer = j["physics layer"];
    json material = j["material"];
    this->_material.dynamic_friction = material["dynamic friction"];
    this->_material.bounciness = material["bounciness"];
    this->_fixed = j["fixed"];
}

json Object::serialise()
{
    // detach collider rbl so it doesn't get included in ser.
    if (this->_renderable_collider)
        this->_renderable_collider->set_parent(nullptr);
    json rv = Transform::serialise();
    // reattach collider rbl
    if (this->_renderable_collider)
        this->_renderable_collider->set_parent(this);

    rv["type"] = "object";
    rv["shape"] = this->_shape.serialise();
    rv["velocity"] = vec2json(this->velocity);
    rv["force"] = vec2json(this->force);
    rv["mass"] = this->mass;
    rv["physics layer"] = this->_layer;
    json material;
    material["dynamic friction"] = this->_material.dynamic_friction;
    material["bounciness"] = this->_material.bounciness;
    rv["material"] = material;
    rv["fixed"] = this->_fixed;

    return rv;
}