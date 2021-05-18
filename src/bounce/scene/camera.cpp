#include <bounce/scene/scene.hpp>
#include <bounce/logging/logger.hpp>

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

void Scene::add_camera(Camera *cam)
{
    this->_cameras[cam->get_name()] = cam;
}

void Scene::remove_camera(const std::string &name)
{
    auto it = this->_cameras.find(name);
    if (it == this->_cameras.end()) {
        Logger::ref() << LL_WARN << "\"" << name << "\" is not the name of a camera in scene \"" << this->get_name() << "\": cannot remove.\n";
    }
    else {
        delete it->second;
        this->_cameras.erase(it);
    }
}

Camera *Scene::get_active_camera() const
{
    return this->_active_camera;
}

Camera *Scene::new_camera(const std::string &name)
{
    auto *c = new Camera(this, {100.0, 100.0}, name);
    this->_cameras[name] = c;
    return c;
}

Camera *Scene::get_camera(const std::string &name) const
{
    auto it = this->_cameras.find(name);
    if (it == this->_cameras.end()) {
        Logger::ref() << LL_ERROR << "\"" << name << "\" is not the name of a camera in scene \"" << this->get_name() << "\".\n";
        throw std::runtime_error("cannot find camera.");
    }
    else {
        return it->second;
    }
}