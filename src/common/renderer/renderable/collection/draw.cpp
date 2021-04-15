#include "collection.hpp"

void CollectionRenderable::draw() const
{
    for (const auto rbl : this->children) {
        if (rbl && rbl->get_visible())
            rbl->draw();
    }
}