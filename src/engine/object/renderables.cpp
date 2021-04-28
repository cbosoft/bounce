#include "object.hpp"
#include "../game/game.hpp"

void Object::get_renderables(std::list<const Renderable *> &out) const
{
    if (Game::ref().should_show_colliders()) {
        this->_renderable_collider->set_size({this->shape.w*2., this->shape.h*2.});
        out.push_back(this->_renderable_collider);
    }
    Transform::get_renderables(out);
}