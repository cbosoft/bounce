#include <bounce/transform/transform.hpp>
#include <bounce/renderer/renderable/renderable.hpp>

json Transform::serialise()
{
    json rv;
    rv["type"] = "transform";
    rv["relative position"] = { this->_relative_position[0], this->_relative_position[1] };
    rv["relative z"] = this->_relative_z;
    rv["scale"] = this->_scale;

    for (auto *rbl : this->_anonymous_renderables) {
        rv["anonymous renderables"].push_back(rbl->serialise());
    }

    for (auto kv : this->_named_renderables) {
        rv["named renderables"][kv.first] = kv.second->serialise();
    }

    return rv;
}