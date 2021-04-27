#pragma once
#include <chrono>

#include "../engine/bounce.hpp"
#include "settings.hpp"

class Projectile final: public Object {
public:
    Projectile(Transform *parent, const arma::vec2 &pos)
            :   Object(parent, pos, false, 1.0)
    {
        this->attach_renderable("proj", new RegularPolygonMeshRenderable(20));
        this->set_colour(Colours::cyan);
    }

    void on_update() override
    {
        double dist = arma::norm(this->get_relative_position());
        if (dist > 100.0) {
            Game::ref().add_event(new TransformDestroyEvent(this));
        }
    }

    void on_collision(Object *other) override
    {
        (void) other;
        Game::ref().add_event(new TransformDestroyEvent(this));
    }
};

class Player final: public Object {
public:
    Player(Scene *parent, const arma::vec2 &position)
            :   Object(parent, position, false, 1.0)
            ,   _command_state({false, false, false, false})
            ,   _speed(1000.0)
            ,   _last_shot(std::chrono::system_clock::now())
            ,   _cooldown_frames(50)
            // ,   _mag(10)
            // ,   _ammo(10)
            // ,   _reload(0)
            // ,   _reload_cooldown(20)
            ,   _score(0.0)
    {
        this->body = new RegularPolygonMeshRenderable(20);
        this->body->set_texture_name("ufo_body");
        this->body->set_size({10.0, 10.0});
        this->attach_renderable("body", body);

        this->gun = new RegularPolygonMeshRenderable(20);
        this->gun->set_texture_name("ufo_gun");
        this->gun->set_size({20.0, 20.0});
        this->attach_renderable("gun", gun);

        this->set_radius(5.0);
    }

    void aim(double angle)
    {
        this->gun->set_angle(angle);
    }

    void score(double amount)
    {
        this->_score += amount;
    }

    void shoot()
    {
        if (this->_cooldown_frames) return;
        this->_cooldown_frames = 50;
        double c = std::cos(this->gun->get_angle()), s = std::sin(this->gun->get_angle());
        arma::vec2 pos = arma::mat22{{c, -s},
                                     {s, c}} * arma::vec2{1, 0};
        auto *projectile = new Projectile(this, pos * this->gun->get_size()[0]*.5 + this->get_position());
        arma::vec2 v = pos * 100 + this->get_velocity();
        // this->add_force(-1e4 * pos);
        projectile->set_velocity(v);
        this->_score -= 1.0;
    }

    double get_ammo_left() const
    {
        return double(this->_score)/1000.0;
    }

    void up() { this->_command_state.move_up = true; }
    void left() { this->_command_state.move_left = true; }
    void down() { this->_command_state.move_down = true; }
    void right() { this->_command_state.move_right = true; }

    void damage(double amount)
    {
        this->_score -= amount;
    }

    void on_update() override
    {
        if (this->_cooldown_frames) this->_cooldown_frames--;
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

        // if (this->_ammo < this->_mag) {
        //     if (!this->_reload--) {
        //         this->_ammo++;
        //         this->_reload = this->_reload_cooldown;
        //     }
        // }
    }

    Renderable *gun, *body;

private:
    struct {
        bool move_up;
        bool move_left;
        bool move_down;
        bool move_right;
    } _command_state;
    double _speed;

    std::chrono::system_clock::time_point _last_shot;
    long _cooldown_frames;
    // long _mag, _ammo, _reload, _reload_cooldown;

    double _score;
};
