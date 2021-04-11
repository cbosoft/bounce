#include "scene.hpp"

const std::string &Scene::get_name() const
{
    return this->_name;
}

const std::vector<PhysicsObject *> &Scene::get_objects() const
{
    return this->_objects;
}
