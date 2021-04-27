#pragma once
#include "../../engine/bounce.hpp"

#include "player.hpp"

class DemoEnemy : public Object {
public:
    DemoEnemy(Transform *parent, const arma::vec2 &position, DemoPlayer *target)
            :   Object(parent, position, 1.0)
            ,   evasive_mult(1.0)
            ,   _target(target)
    {
        this->body = new RegularPolygonMeshRenderable(20);
        body->set_colour(Colour::from_rgb(255, 225, 225));
        body->set_texture_name("enemy");
        body->set_size({5, 5});
        this->set_radius(2.5);
        this->attach_renderable(body);
    }

    void face_forward()
    {
        arma::vec2 vd = arma::normalise(this->get_velocity());
        double len = arma::norm(vd);
        if (len > 0.0) {
            double angle = std::acos(vd[0] / len);
            if (vd[1] < 0.0) angle *= -1.0;
            this->body->set_angle(angle);
        }
    }

    void head_toward_target()
    {
        auto dp = this->_target->get_position() - this->get_position();
        arma::vec2 f = arma::normalise(dp)*5e3;
        this->set_force(f);
    }

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

    void maybe_change_state()
    {
        if (arma::randu() < 1./60.) {
            this->_state = ENEMY_EVASIVE;
            this->cooldown = 10;
            if (arma::randu() < 0.1)
                this->evasive_mult *= -1.0;
        }
    }

    void evasive_manoeuvre()
    {
        if (this->cooldown-- > 0) {
            auto dp = this->_target->get_position() - this->get_position();
            arma::vec2 perp{-dp[1], dp[0]};
            arma::vec2 f = arma::normalise(perp)*5e3*this->evasive_mult;
            this->set_force(f);
        }
        else {
            this->_state = ENEMY_ATTACKING;
        }
    }

    void on_update() override
    {
        switch (this->_state) {
            case ENEMY_ATTACKING:
                this->head_toward_target();
                this->maybe_change_state();
                break;

            case ENEMY_EVASIVE:
                this->evasive_manoeuvre();
                break;
        }

        this->face_forward();
        this->enforce_max_vel();
    }

    void on_collision(Object *other) override
    {
        if ((Transform *)other == (Transform *)this->_target) {
            this->_target->damage(10);
        }
        else {
            this->_target->score(100);
            Game::ref().add_event(new TransformDestroyEvent(this));
        }
        Game::ref().add_event(new TemporaryTimePause(10));
    }

private:
    enum AI_STATE { ENEMY_ATTACKING, ENEMY_EVASIVE };
    AI_STATE _state = ENEMY_ATTACKING;
    int cooldown = 0;
    double evasive_mult;
    DemoPlayer *_target;
    MeshRenderable *body;
};