#include <bounce/physics/collider/collider.hpp>

void Collider::set_shape_rectangle(double w, double h)
{
    this->_shape_type = ST_RECT;
    this->_hw = w*.5;
    this->_hh = h*.5;

    if (this->_renderable_collider) {
        this->remove_child(this->_renderable_collider);
        delete this->_renderable_collider;
        this->_renderable_collider = nullptr;
    }

    this->_renderable_collider = new RectangleMeshRenderable(1, 1);

    this->_renderable_collider->set_border_size(0.5);
    this->_renderable_collider->set_colour(Colours::clear);
    this->_renderable_collider->set_border_colour(Colours::yellow);
    this->_renderable_collider->set_parent(this);
    this->_renderable_collider->set_z(1000);
}

void Collider::set_shape_circle(double radius)
{
    this->_shape_type = ST_CIRCLE;
    this->_hw = this->_hh = radius;

    if (this->_renderable_collider) {
        this->remove_child(this->_renderable_collider);
        delete this->_renderable_collider;
        this->_renderable_collider = nullptr;
    }

    this->_renderable_collider = new RegularPolygonMeshRenderable(20);

    this->_renderable_collider->set_border_size(0.5);
    this->_renderable_collider->set_colour(Colours::clear);
    this->_renderable_collider->set_border_colour(Colours::yellow);
    this->_renderable_collider->set_parent(this);
    this->_renderable_collider->set_z(1000);
}

void Collider::get_rect_half_extents(double &hw, double &hh) const
{
    hw = this->_hw;
    hh = this->_hh;
}

void Collider::get_circle_radius(double &r) const
{
    r = this->_hw;
}

ShapeType Collider::get_shape_type() const
{
    return this->_shape_type;
}
