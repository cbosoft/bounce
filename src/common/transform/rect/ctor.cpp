#include "rect.hpp"

RectTransform::RectTransform(Transform *parent, const arma::vec2 &size)
:   Transform(parent)
,   _size(size)
{

}