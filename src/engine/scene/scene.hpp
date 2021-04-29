#pragma once

#include <map>
#include <string>
#include "../input/context/context.hpp"
#include "../object/object.hpp"
#include "../transform/transform.hpp"
#include "../transform/rect/rect.hpp"
#include "../physics/field/field.hpp"

class Scene: public InputContext, public Transform {
public:
    Scene(const std::string &name);

    virtual void on_activate() {}
    virtual void on_deactivate() {}
    virtual void on_update() {}

    const std::string &get_name() const;
    std::vector<Object *> find_objects_near_to(Transform *t, double radius) const;

    void add_field(ForceField *field);
    const std::vector<ForceField *> &get_fields() const;

    void set_active_camera(const std::string &name);
    void add_camera(const std::string &name, RectTransform *t);
    RectTransform *new_camera(const std::string &name);
    void remove_camera(const std::string &name);
    RectTransform *get_active_camera() const;

private:
    std::vector<ForceField *> _fields;
    std::string _name;
    std::map<std::string, RectTransform *> _cameras;
    RectTransform *_active_camera;
};