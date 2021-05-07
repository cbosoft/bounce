#pragma once
#include <chrono>

#include <bounce/bounce.hpp>

class DemoProjectile final: public Object {
public:
    DemoProjectile(Transform *parent, const arma::vec2 &pos)
            :   Object(parent)
    {
        this->attach_renderable("proj", new RegularPolygonMeshRenderable(20));
        this->set_colour(Colours::cyan);
        this->set_position(pos);
        this->set_identifier("projectile");
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
            :   Object(parent)
            ,   _speed(1000.0)
            ,   _hp(10.0)
            ,   _max_hp(10.0)
            ,   _last_shot(std::chrono::system_clock::now())
            ,   _last_got_hurt(std::chrono::system_clock::now())
            ,   _cooldown_frames(50)
            ,   _score(0.0)
    {
        this->set_position(position);
        this->set_identifier("player");

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

    void damage(double amount)
    {
        if (!this->invincible) {
            this->_hp -= amount;
            this->invincible = true;
            this->body->set_colour(Colour::from_grayscale(255, 127));
            this->_last_got_hurt = std::chrono::system_clock::now();
        }
    }

    [[nodiscard]] double get_hp_fraction() const
    {
        return this->_hp/this->_max_hp;
    }

    void up_pressed() { this->_dir[1] += 1; }
    void up_released() { this->_dir[1] -= 1; }
    void left_pressed() { this->_dir[0] -= 1; }
    void left_released() { this->_dir[0] += 1; }
    void down_pressed() { this->_dir[1] -= 1; }
    void down_released() { this->_dir[1] += 1; }
    void right_pressed() { this->_dir[0] += 1; }
    void right_released() { this->_dir[0] -= 1; }

    void enforce_max_vel()
    {
        auto v = this->get_velocity();
        double vm = arma::norm(v);
        constexpr double MAX_VEL = 50.0;
        if (vm > MAX_VEL) {
            auto nv = arma::normalise(v);
            this->set_velocity(MAX_VEL*nv);
        }
    }

    void on_update() override
    {

        // this->set_velocity(dir*this->_speed);
        // or
        this->add_force(this->_dir*this->_speed);

        // arma::vec2 vd = arma::normalise(this->get_velocity());
        // arma::vec2 f = vd%arma::pow(this->get_velocity(), 2.0);
        // this->add_force(-.1*f);
        this->enforce_max_vel();
        // double len = arma::norm(vd);
        // if (len > 0.0) {
        //     double angle = std::acos(vd[0] / len);
        //     if (vd[1] < 0.0) angle *= -1.0;
        //     this->body->set_angle(angle);
        // }
        this->body->set_angle(this->gun->get_angle());

        auto now = std::chrono::system_clock::now();

        if (this->_should_shoot) {
            long time_since_shoot = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_last_shot).count();
            if (time_since_shoot > 100) {
                double c = std::cos(this->gun->get_angle()), s = std::sin(this->gun->get_angle());
                arma::vec2 pos = arma::mat22{{c, -s},
                                             {s, c}} * arma::vec2{1, 0};
                auto *projectile = new DemoProjectile(this, pos * this->gun->get_size()[0] * .5 + this->get_position());
                arma::vec2 v = pos * 100 + this->get_velocity();
                // this->add_force(-1e4 * pos);
                projectile->set_velocity(v);
                this->_score -= 1;
                this->_last_shot = now;
            }
        }

        if (this->invincible) {
            long time_since_hurt = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_last_got_hurt).count();
            if (time_since_hurt > 300) {
                this->invincible = false;
                this->body->set_colour(Colours::white);
            }
        }

        if (this->_hp < 1.0) {
            Game::ref().add_event(new PushSceneTransitionEvent("shooter end game"));
        }
    }

    Renderable *gun, *body;

private:
    arma::vec2 _dir{0, 0};
    double _speed, _hp, _max_hp;
    bool _should_shoot;
    int invincible;

    std::chrono::system_clock::time_point _last_shot, _last_got_hurt;
    long _cooldown_frames, _score;
};

class DemoPlayerHPBar final: public BarGraph {
public:
    DemoPlayerHPBar(DemoPlayer *player)
    :   BarGraph(100, 10)
    ,   player(player)
    {

    }

private:

    double measure_value() const override
    {
        return this->player->get_hp_fraction();
    }

    double measure_maximum() const override
    {
        return 1.0;
    }

    DemoPlayer *player;
};
