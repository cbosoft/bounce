#include <bounce/scene/scene.hpp>

Scene::Scene(json j, int dummy)
:   Scene(std::string(j["name"]))
{
    (void) dummy;
    this->_insubstantial = j["insubstantial"];
    // TODO fields

    // children have already been de-serialised; add named cameras
    std::list<Camera *> cameras;
    this->find_in_children_cast("camera", cameras);
    for (auto *camera : cameras) {
        // TODO fix memory leak: this will re-add the default camera which would have been created in the ctor
        this->add_camera(camera);
    }
    this->set_active_camera(j["active camera"]);

}

json Scene::serialise()
{
    json rv = Transform::serialise();
    rv["type"] = "scene";
    rv["name"] = this->_name;
    rv["insubstantial"] = this->_insubstantial;
    rv["active camera"] = this->_active_camera->get_name();
    // TODO fields
    return rv;
}