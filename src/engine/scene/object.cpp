#include "scene.hpp"
#include "../game/game.hpp"

std::vector<Object *> Scene::find_objects_near_to(Transform *t, double radius) const
{
    std::vector <Object *> rv;
    (void) t;
    (void) radius;
    // auto a = t->get_position();
    // for (auto *object : this->get_children()) {
    //     auto b = object->get_position();
    //     double dist = arma::norm(b - a);
    //     if (dist < radius)
    //         rv.push_back(object);
    // }
    return rv;
}
