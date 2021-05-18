#include <bounce/transform/transform.hpp>
#include <bounce/renderer/renderable/renderable.hpp>

json Transform::serialise()
{
    json rv;
    rv["type"] = "transform";
    rv["relative position"] = { this->_relative_position[0], this->_relative_position[1] };
    rv["relative z"] = this->_relative_z;
    rv["scale"] = this->_scale;

    for (auto *child : this->_children) {
        rv["children"].push_back(child->serialise());
    }

    return rv;
}