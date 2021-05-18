#include <bounce/transform/rect/rect.hpp>

RectTransform::RectTransform(json j)
:   Transform(j)
,   _size({1, 1})
,   _bl(new Transform(this))
,   _br(new Transform(this))
,   _tl(new Transform(this))
,   _tr(new Transform(this))
{
    arma::vec2 size = {j["size"][0], j["size"][1]};
    this->set_size(size);
}

json RectTransform::serialise()
{
    json rv = Transform::serialise();
    rv["type"] = "rect transform";
    rv["size"] = {this->_size[0], this->_size[1]};
    return rv;
}