#pragma once

#include "../../engine/bounce.hpp"
#include "platformer_player.hpp"


class Foo : public Object {
public:
    Foo(Transform *parent)
    : Object(parent, {0, 0}, 1.0, 1.0)
    ,   _dir{0.0}
    ,   _jump{false}
    ,   _can_jump{false}
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
        std::cerr << "colliding!" << std::endl;
        this->_can_jump = true;
    }

    void on_physics_update() override
    {
        double fy = 0.0;
        if (this->_can_jump && this->_jump) {
            this->_can_jump = this->_jump = false;
            fy = 1e4;
        }
        double fx = this->_dir*100.0;
        this->_dir = 0.0;
        this->add_force({fx, fy});
        //double vy = this->get_velocity()[1];
        //this->set_velocity({this->_dir*10., vy});
    }

private:
    double _dir;
    bool _jump, _can_jump;
};

class DemoPlatformer final : public Scene {
public:
    DemoPlatformer()
    :   Scene("demo platformer")
    {
        auto *floor = new Object(this, {0, -50}, true);
        floor->set_shape(CollisionShape::rectangle(100, 1));
        auto *leftwall = new Object(this, {-50, 0}, true);
        leftwall->set_shape(CollisionShape::rectangle(1, 1000));
        auto *rightwall = new Object(this, {50, 0}, true);
        rightwall->set_shape(CollisionShape::rectangle(1, 1000));

        auto *box = new Object(this, {0, 50}, 1.0, 1.0);
        box->set_shape(CollisionShape::rectangle(1, 1));

        this->player = new Foo(this);
        //(void) box2;

        // this->player = new DemoPlatformerPlayer(this);
        // this->player->set_position({5, 0});

        auto *gravity = new UnboundedLinearForceField(0, 0, 0, -10);
        this->add_field(gravity);

        Game::ref().show_colliders();
        this->get_active_camera()->set_parent(this->player);
    }

    void back() override { Game::ref().pop_active_scene(); }

    void left() override { this->player->left(); }
    void right() override { this->player->right(); }
    void action() override { this->player->jump(); }

private:
    Foo *player;
};