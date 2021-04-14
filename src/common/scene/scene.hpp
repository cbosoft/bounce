#pragma once

#include <map>
#include <string>
#include "../input/context/context.hpp"
#include "../object/object.hpp"
#include "../transform/transform.hpp"
#include "../transform/rect/rect.hpp"

class Scene: public InputContext, public Transform {
public:
    Scene(Game *game, const std::string &name);

    virtual void on_activate() {}

    const std::string &get_name() const;
    const std::vector<Object *> &get_objects() const;
    void add_object(Object *object);
    const std::vector<Renderable *> &get_floating_renderables() const;
    void add_floating_renderable(Renderable *rbl);
    std::vector<Object *> find_objects_near_to(Transform *t, double radius) const;

    void set_active_camera(const std::string &name);
    void add_camera(const std::string &name, RectTransform *t);
    RectTransform *new_camera(const std::string &name);
    void remove_camera(const std::string &name);
    RectTransform *get_active_camera() const;

private:
    std::vector<Renderable *> _floating_renderables;
    std::vector<Object *> _objects;
    std::string _name;
    std::map<std::string, RectTransform *> _cameras;
    RectTransform *_active_camera;
};