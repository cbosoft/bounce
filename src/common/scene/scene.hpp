#pragma once
#include "../input/context/context.hpp"
#include "../physics/object/object.hpp"
#include "../transform/transform.hpp"

class Scene: public InputContext, public Transform {
public:
    Scene(Game *game, const std::string &name);

    const std::string &get_name() const;
    const std::vector<PhysicsObject *> &get_objects() const;
    void add_object(PhysicsObject *object);

private:
    std::vector<PhysicsObject *> _objects;
    std::string _name;
};