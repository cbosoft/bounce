#include "scene.hpp"
#include "../game/game.hpp"

void Scene::add_object(Object *object)
{
    this->_objects.emplace_back(object);
    object->set_parent(this);
    this->get_game()->add_object(object);
}

std::vector<Object *> Scene::find_objects_near_to(Transform *t, double radius) const
{
    std::vector <Object *> rv;
    auto a = t->get_position();
    for (auto *object : this->get_objects()) {
        auto b = object->get_position();
        double dist = arma::norm(b - a);
        if (dist < radius)
            rv.push_back(object);
    }
    return rv;
}
