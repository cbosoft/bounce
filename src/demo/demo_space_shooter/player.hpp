#pragma once
#include <chrono>

#include <bounce/bounce.hpp>

class DemoProjectile final: public Object {
public:
    DemoProjectile(Transform *parent, const arma::vec2 &pos)
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

class DemoPlayer final: public Object {
public:
    DemoPlayer(Scene *parent, const arma::vec2 &position)
            :   Object(parent, position, false, 1.0)
            ,   _speed(1000.0)
            ,   _last_shot(std::chrono::system_clock::now())
            ,   _cooldown_frames(50)
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

        this->set_shape(CollisionShape::circle(5.0));
    }

    void aim(double angle)
    {
        this->gun->set_angle(angle);
    }

    void shoot()
    {
        this->_should_shoot = true;
    }

    void dont_shoot()
    {
        this->_should_shoot = false;
    }

    long get_score() const
    {
        return this->_score;
    }

    void score(long amount)
    {
        this->_score += amount;
    }

    void damage(long amount)
    {
        this->_score -= amount;
    }

    void up_pressed() { this->_dir[1] += 1; }
    void up_released() { this->_dir[1] -= 1; }
    void left_pressed() { this->_dir[0] -= 1; }
    void left_released() { this->_dir[0] += 1; }
    void down_pressed() { this->_dir[1] -= 1; }
    void down_released() { this->_dir[1] += 1; }
    void right_pressed() { this->_dir[0] += 1; }
    void right_released() { this->_dir[0] -= 1; }

    void on_update() override
    {

        // this->set_velocity(dir*this->_speed);
        // or
        this->add_force(this->_dir*this->_speed);

        arma::vec2 vd = arma::normalise(this->get_velocity());
        arma::vec2 f = vd%arma::pow(this->get_velocity(), 2.0);
        this->add_force(-.1*f);

        // double len = arma::norm(vd);
        // if (len > 0.0) {
        //     double angle = std::acos(vd[0] / len);
        //     if (vd[1] < 0.0) angle *= -1.0;
        //     this->body->set_angle(angle);
        // }
        this->body->set_angle(this->gun->get_angle());

        if (this->_cooldown_frames) this->_cooldown_frames--;
        if (!this->_cooldown_frames && this->_should_shoot) {
            this->_cooldown_frames = 10;
            double c = std::cos(this->gun->get_angle()), s = std::sin(this->gun->get_angle());
            arma::vec2 pos = arma::mat22{{c, -s},
                                         {s, c}} * arma::vec2{1, 0};
            auto *projectile = new DemoProjectile(this, pos * this->gun->get_size()[0] * .5 + this->get_position());
            arma::vec2 v = pos * 100 + this->get_velocity();
            // this->add_force(-1e4 * pos);
            projectile->set_velocity(v);
            this->_score -= 1;
        }
    }

    Renderable *gun, *body;

private:
    arma::vec2 _dir{0, 0};
    double _speed;
    bool _should_shoot;

    std::chrono::system_clock::time_point _last_shot;
    long _cooldown_frames, _score;
};
