#include <bounce/physics/rigidbody/rigidbody.hpp>

Rigidbody::Rigidbody(json j)
:   Collider(j)
,   _velocity({0, 0})
,   _previous_velocity({0, 0})
,   _force({0, 0})
,   _mass(1.0)
,   _inv_mass(1.0)
,   _material({0.0, 0.0})
,   _fixed(false)
{
    this->_velocity = jsonvec2(j["velocity"]);
    this->_previous_velocity = jsonvec2(j["previous velocity"]);
    this->_force = jsonvec2(j["force"]);
    this->set_mass(j["mass"]);
    json material = j["material"];
    this->_material.dynamic_friction = material["dynamic friction"];
    this->_material.bounciness = material["bounciness"];
    this->_fixed = j["fixed"];
}

json Rigidbody::serialise()
{
    json rv = Collider::serialise();

    rv["type"] = "rigidbody";
    rv["velocity"] = vec2json(this->_velocity);
    rv["previous velocity"] = vec2json(this->_previous_velocity);
    rv["force"] = vec2json(this->_force);
    rv["mass"] = this->_mass;
    json material;
    material["dynamic friction"] = this->_material.dynamic_friction;
    material["bounciness"] = this->_material.bounciness;
    rv["material"] = material;
    rv["fixed"] = this->_fixed;

    return rv;
}
