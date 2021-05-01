#include <bounce/scene/scene.hpp>

Scene::Scene(const std::string &name)
    :   _insubstantial{false}
    ,   _name(name)
    ,   _active_camera(nullptr)
{
    this->_active_camera = this->new_camera("default");
}