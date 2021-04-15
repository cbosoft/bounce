#pragma once

#include "../common/bounce.hpp"
#include "settings.hpp"

class Player final: public Object {
public:
    Player(Transform *parent, const arma::vec2 &position)
            :   Object(parent, position, false, 1.0)
            ,   _command_state({false, false, false, false})
            ,   _speed(1000.0)
    {

    }

    void up() { this->_command_state.move_up = true; }
    void left() { this->_command_state.move_left = true; }
    void down() { this->_command_state.move_down = true; }
    void right() { this->_command_state.move_right = true; }

    void update() override
    {
        arma::vec2 dir{0,0};
        if (this->_command_state.move_up)    dir[1] += 1.0;
        if (this->_command_state.move_down)  dir[1] -= 1.0;
        if (this->_command_state.move_left)  dir[0] -= 1.0;
        if (this->_command_state.move_right) dir[0] += 1.0;

        // this->set_velocity(dir*this->_speed);
        // or
        this->add_force(dir*this->_speed);

        arma::vec2 vd = arma::normalise(this->get_velocity());
        arma::vec2 f = vd%arma::pow(this->get_velocity(), 2.0);
        this->add_force(-.1*f);

        this->_command_state = {false, false, false, false};

    }

private:
    struct {
        bool move_up;
        bool move_left;
        bool move_down;
        bool move_right;
    } _command_state;
    double _speed;
};
