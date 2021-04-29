#pragma once

#include "../../engine/bounce.hpp"

class DemoPlatformerPlayer final : public Object{
public:
    DemoPlatformerPlayer(Transform *parent)
        :   Object(parent, {0, 0}, false)
        ,   _dir{0.0}
        ,   _jump{false}
    {
        this->set_shape(CollisionShape::rectangle(1, 1));
        this->set_friction(0.9);
        this->set_bounciness(0.1);
    }

    void left() { this->_dir -= 1.0; }
    void right() { this->_dir += 1.0; }
    void jump() { this->_jump = true; }

    void on_collision(Object *other) override
    {
        std::cerr << "colliding!" << std::endl;
        this->_can_jump = true;
    }

    void on_physics_update() override
    {
        if (this->_can_jump && this->_jump) {
            this->_can_jump = this->_jump = false;
            this->add_force({0.0, 1e3});
        }
        this->set_velocity({this->_dir*10.0, 0.0});
    }

private:
    double _dir;
    bool _jump, _can_jump;
};