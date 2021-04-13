#include "collection.hpp"

void CollectionRenderable::draw() const
{
    for (const auto rbl : this->children) {
        rbl->draw();
    }
}