#include <bounce/object/object.hpp>
#include <bounce/game/game.hpp>

void Object::get_renderables(std::list<const Renderable *> &out) const
{
    if (Game::ref().should_show_colliders() && this->_renderable_collider) {
        this->_renderable_collider->set_size({this->_shape.w, this->_shape.h});
        this->_renderable_collider->show();
    }
    else if (this->_renderable_collider) {
        this->_renderable_collider->hide();
    }
    Transform::get_renderables(out);
}
