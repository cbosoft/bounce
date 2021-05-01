#include <bounce/scene/scene.hpp>

void Scene::set_active_camera(const std::string &name)
{
    auto it = this->_cameras.find(name);
    if (it == this->_cameras.end()) {
        std::cerr << "w) \"" << name << "\" is not the name of an active camera in scene \"" << this->get_name() << "\": cannot set active." << std::endl;
    }
    else {
        this->_active_camera = it->second;
    }
}

void Scene::add_camera(const std::string &name, RectTransform *t)
{
    this->_cameras[name] = t;
}

void Scene::remove_camera(const std::string &name)
{
    auto it = this->_cameras.find(name);
    if (it == this->_cameras.end()) {
        std::cerr << "w) \"" << name << "\" is not the name of an active camera in scene \"" << this->get_name() << "\": cannot remove." << std::endl;
    }
    else {
        delete it->second;
        this->_cameras.erase(it);
    }
}

RectTransform *Scene::get_active_camera() const
{
    return this->_active_camera;
}

RectTransform *Scene::new_camera(const std::string &name)
{
    auto *c = new RectTransform(this, {100.0, 100.0});
    this->_cameras[name] = c;
    return c;
}