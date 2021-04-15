#include "scene.hpp"

const std::string &Scene::get_name() const
{
    return this->_name;
}

const std::vector<Object *> &Scene::get_objects() const
{
    return this->_objects;
}

void Scene::add_field(ForceField *field)
{
    this->_fields.push_back(field);
}

const std::vector<ForceField *> &Scene::get_fields() const
{
    return this->_fields;
}
