#include "transform.hpp"
#include "../renderer/renderable/renderable.hpp"

void Transform::attach_renderable(const std::string &name, Renderable *rbl)
{
    this->_named_renderables[name] = rbl;
    rbl->set_parent(this);
}

void Transform::attach_renderable(Renderable *rbl)
{
    this->_anonymous_renderables.push_back(rbl);
    rbl->set_parent(this);
}

void Transform::get_renderables(std::list<const Renderable *> &out) const
{
    for (const auto &kv : this->_named_renderables) {
        out.push_back(kv.second);
    }
    for (const Renderable *rbl : this->_anonymous_renderables) {
        out.push_back(rbl);
    }
    for (const auto child : this->_children) {
        child->get_renderables(out);
    }
}