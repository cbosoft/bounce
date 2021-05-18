#include <bounce/transform/transform.hpp>
#include <bounce/renderer/renderable/renderable.hpp>
#include <bounce/game/game.hpp>

Transform::Transform(json j)
        :   Transform()
{
    this->_relative_position = { j["relative position"][0], j["relative position"][1] };
    this->_relative_z = j["relative z"];
    this->_scale = j["scale"];

    for (const json &child : j["children"]) {
        Transform *ch = Game::ref().deserialise(child);
        ch->set_parent(this);
    }

    for (const json &tag : j["tags"]) {
        std::string stag = tag;
        this->add_tag(stag);
    }
}

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

    json tags;
    for (const auto &tag : this->_tags) {
        tags.push_back(tag);
    }
    rv["tags"] = tags;

    return rv;
}