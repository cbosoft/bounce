#include "scene.hpp"

const std::vector<Renderable*> &Scene::get_floating_renderables() const
{
    return this->_floating_renderables;
}

void Scene::add_floating_renderable(Renderable *rbl)
{
    this->_floating_renderables.push_back(rbl);
}