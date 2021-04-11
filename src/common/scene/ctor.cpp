#include "scene.hpp"

Scene::Scene(Game *game, const std::string &name)
: InputContext(game)
, _name(name)
{
    // do nothing
}