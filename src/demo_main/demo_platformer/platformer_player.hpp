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
        this->set_bounciness(0.1);
        this->set_friction(0.01);
    }

    void left() { this->_dir = -1.0; }
    void right() { this->_dir = 1.0; }
    void jump() { this->_jump = true; }

    void on_collision(Object *other) override
    {
        this->_on_ground = true;
    }

    void on_update() override
    {
        this->_dir = 0.0;
        this->_on_ground = false;
    }

    void on_physics_update() override
    {
        double fy = 0.0;
        if (this->_on_ground && this->_jump) {
            this->_on_ground = this->_jump = false;
            fy = 1.5e4;
        }

        double spd_mult = this->_on_ground ? 1.0 : 0.1;
        this->add_force({this->_dir*300.0*spd_mult, fy});

        this->_on_ground = false;
    }

private:
    double _dir;
    bool _jump, _on_ground;
};