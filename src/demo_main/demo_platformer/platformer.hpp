#pragma once

#include "../../engine/bounce.hpp"
#include "platformer_player.hpp"


class DemoPlatformer final : public Scene {
public:
    DemoPlatformer()
    :   Scene("demo platformer")
    {
        {
            auto *platform = new Object(this, {0, -50}, true);
            platform->set_shape(CollisionShape::rectangle(50, 1));
        }
        {
            auto *platform = new Object(this, {25, -25}, true);
            platform->set_shape(CollisionShape::rectangle(50, 1));
        }
        {
            auto *platform = new Object(this, {50, 0}, true);
            platform->set_shape(CollisionShape::rectangle(50, 1));
        }

        //auto *box = new Object(this, {0, 50}, 1.0, 1.0);
        //box->set_shape(CollisionShape::rectangle(1, 1));

        this->player = new DemoPlatformerPlayer(this);
        this->player->set_position({0, -45});

        auto *gravity = new UnboundedLinearForceField(0, 0, 0, -10);
        this->add_field(gravity);

        this->get_active_camera()->set_parent(this->player);
    }

    void on_activate() override { Game::ref().show_colliders(); }
    void on_deactivate() override { Game::ref().hide_colliders(); }

    void back() override { Game::ref().pop_active_scene(); }

    void left() override { this->player->left(); }
    void right() override { this->player->right(); }
    void action() override { this->player->jump(); }

private:
    DemoPlatformerPlayer *player;
};