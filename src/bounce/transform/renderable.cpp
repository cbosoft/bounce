#include <bounce/transform/transform.hpp>
#include <bounce/renderer/renderable/renderable.hpp>

void Transform::get_renderables(std::list<const Renderable *> &out) const
{
    if (this->is_active()) {
        for (const auto child : this->_children) {
            child->get_renderables(out);
        }
    }
}