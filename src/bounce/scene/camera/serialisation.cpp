#include <bounce/scene/camera/camera.hpp>

Camera::Camera(json j)
:   RectTransform(j)
,   _name(j["name"])
{
    // do nothing
}

json Camera::serialise()
{
    json rv = RectTransform::serialise();
    rv["type"] = "camera";
    rv["name"] = this->_name;
    return rv;
}