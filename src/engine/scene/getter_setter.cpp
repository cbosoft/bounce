#include "scene.hpp"

const std::string &Scene::get_name() const
{
    return this->_name;
}

void Scene::add_field(ForceField *field)
{
    this->_fields.push_back(field);
}

const std::vector<ForceField *> &Scene::get_fields() const
{
    return this->_fields;
}

bool Scene::is_insubstantial() const
{
    return this->_insubstantial;
}
