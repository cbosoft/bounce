#include <bounce/transform/rect/rect.hpp>

RectTransform::RectTransform(Transform *parent, const arma::vec2 &size)
:   Transform(parent)
,   _size({1, 1})
,   _bl(new Transform(this))
,   _br(new Transform(this))
,   _tl(new Transform(this))
,   _tr(new Transform(this))
{
    this->set_size(size);
    this->add_tag("rectangle transform");
}