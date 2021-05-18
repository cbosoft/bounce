#include <bounce/scene/camera/camera.hpp>

Camera::Camera(Transform *parent, const arma::vec2 &size, const std::string &name)
:   RectTransform(parent, size)
,   _name(name)
{
    this->add_tag("camera");
}