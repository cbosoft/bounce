#include "scene.hpp"

Scene::Scene(Game *game, const std::string &name)
: InputContext(game)
, _name(name)
, _active_camera(nullptr)
{
    this->_active_camera = this->new_camera("default");
}