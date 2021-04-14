#include "scene.hpp"
#include "../game/game.hpp"

void Scene::add_object(Object *object)
{
    this->_objects.emplace_back(object);
    object->set_parent(this);
    this->get_game()->add_object(object);
}
