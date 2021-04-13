#include "collection.hpp"

void CollectionRenderable::add_child(Renderable *rbl)
{
    rbl->set_parent(this);
    this->children.emplace_back(rbl);
}