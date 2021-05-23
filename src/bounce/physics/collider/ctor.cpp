#include <bounce/physics/collider/collider.hpp>

Collider::Collider(Transform *parent)
:   Transform(parent)
,   _hw(.5)
,   _hh(.5)
,   _shape_type(ST_RECT)
,   _touching_flags(0)
,   _interaction_mask(1)
,   _renderable_collider(nullptr)
{
    this->set_shape_rectangle(1.0, 1.0);
    this->add_tag("collider");
}