#include <bounce/physics/collider/collider.hpp>

Collider::Collider(json j)
:   Transform(j)
,   _hw(.5)
,   _hh(.5)
,   _shape_type(ST_RECT)
,   _touching_flags(0)
,   _interaction_mask(1)
,   _renderable_collider(nullptr)
{
    std::string str_st = j["shape"]["type"];
    if (str_st == "rectangle") {
        double w = j["shape"]["width"];
        double h = j["shape"]["height"];
        this->set_shape_rectangle(w, h);
    }
    else {
        double radius = j["shape"]["radius"];
        this->set_shape_circle(radius);
    }

    this->_touching_flags = j["touching flags"];
    this->_interaction_mask = j["interaction mask"];
}

json Collider::serialise()
{
    // detach collider rbl so it doesn't get included in ser.
    if (this->_renderable_collider)
        this->_renderable_collider->set_parent(nullptr);
    json rv = Transform::serialise();
    // reattach collider rbl
    if (this->_renderable_collider)
        this->_renderable_collider->set_parent(this);

    rv["type"] = "collider";
    json shape;
    switch (this->_shape_type) {
        case ST_RECT:
            shape["type"] = "rectangle";
            shape["width"] = 2.*this->_hw;
            shape["height"] = 2.*this->_hh;
            break;
        case ST_CIRCLE:
            shape["type"] = "circle";
            shape["radius"] = this->_hw;
            break;
    }
    rv["shape"] = shape;
    rv["interaction mask"] = this->_interaction_mask;
    rv["touching flags"] = this->_touching_flags;
    return rv;
}