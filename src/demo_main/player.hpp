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
        auto *col = new CollectionRenderable();
        this->set_renderable(col);
        this->gun = new CircleRenderable();
        this->gun->set_texture_name("gun");
        this->gun->set_scale(5.0);
        this->body = new CircleRenderable();
        this->body->set_texture_name("body");
        this->body->set_scale(10.0);
        col->add_child(body);
        col->add_child(gun);
    }

    void aim(double angle)
    {
        this->gun->set_angle(angle);
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

        double len = arma::norm(vd);
        if (len > 0.0) {
            double angle = std::acos(vd[0] / len);
            if (vd[1] < 0.0) angle *= -1.0;
            this->body->set_angle(angle);
        }

    }

private:
    struct {
        bool move_up;
        bool move_left;
        bool move_down;
        bool move_right;
    } _command_state;
    double _speed;

    Renderable *gun, *body;
};
