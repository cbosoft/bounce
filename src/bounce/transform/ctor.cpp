#include <bounce/transform/transform.hpp>
#include <bounce/game/game.hpp>

Transform::Transform()
:   _parent{nullptr}
,   _relative_position({0.0, 0.0})
,   _active{true}
,   _scale(1.0)
,   _relative_z(0)
{
    // do nothing
}

Transform::Transform(Transform *parent)
: Transform()
{
    this->set_parent(parent);
}

Transform::Transform(Transform *parent, const arma::vec2 &position)
: Transform(parent)
{
    this->set_position(position);
}

Transform::Transform(json j)
:   Transform()
{
    this->_relative_position = { j["relative position"][0], j["relative position"][1] };
    this->_relative_z = j["relative z"];
    this->_scale = j["scale"];

    for (json child : j["children"]) {
        Transform *ch = Game::ref().deserialise(child);
        ch->set_parent(ch);
    }
}
