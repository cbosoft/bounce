#pragma once
#include "../input/context/context.hpp"
#include "../physics/object/object.hpp"
#include "../transform/transform.hpp"

class Scene: public InputContext, public Transform {
public:
    Scene(Game *game, const std::string &name);

    virtual void on_activate() {}

    const std::string &get_name() const;
    const std::vector<PhysicsObject *> &get_objects() const;
    void add_object(PhysicsObject *object);
    const std::vector<Renderable *> &get_floating_renderables() const;
    void add_floating_renderable(Renderable *rbl);

private:
    std::vector<Renderable *> _floating_renderables;
    std::vector<PhysicsObject *> _objects;
    std::string _name;
};