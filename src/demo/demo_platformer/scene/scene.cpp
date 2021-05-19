#include "scene.hpp"

DemoPlatformer::DemoPlatformer()
:   Scene("demo platformer")
{
    {
        auto *platform = new Object(this);
        platform->set_fixed(true);
        platform->set_position({0, -50});
        platform->set_shape(CollisionShape::rectangle(30, 10));
        auto *rbl = new RectangleMeshRenderable(30, 10);
        rbl->set_texture_name("block_3x1");
        rbl->set_parent(platform);
    }
    {
        auto *platform = new Object(this);
        platform->set_fixed(true);
        platform->set_position({25, -25});
        platform->set_shape(CollisionShape::rectangle(30, 10));
        auto *rbl = new RectangleMeshRenderable(30, 10);
        rbl->set_texture_name("block_3x1");
        rbl->set_parent(platform);
    }
    {
        auto *platform = new Object(this);
        platform->set_fixed(true);
        platform->set_position({50, 0});
        platform->set_shape(CollisionShape::rectangle(30, 10));
        auto *rbl = new RectangleMeshRenderable(30, 10);
        rbl->set_texture_name("block_3x1");
        rbl->set_parent(platform);
    }

    this->player = new DemoPlatformerPlayer(this);
    this->player->set_position({0, -15});

    this->add_field(new GravityField(10));

    this->get_active_camera()->set_parent(this->player);
}

void DemoPlatformer::on_activate()
{
    Game::ref().show_colliders();
    PhysicsEngine::ref().set_timescale(3.0);
}

void DemoPlatformer::on_deactivate()
{
    Game::ref().hide_colliders();
    PhysicsEngine::ref().set_timescale(1.0);
}

void DemoPlatformer::back_pressed()
{
    Game::ref().pop_active_scene();
}

void DemoPlatformer::left_pressed()
{
    this->player->left_pressed();
}

void DemoPlatformer::left_released()
{
    this->player->left_released();
}

void DemoPlatformer::right_pressed()
{
    this->player->right_pressed();
}

void DemoPlatformer::right_released()
{
    this->player->right_released();
}

void DemoPlatformer::action_pressed()
{
    this->player->jump_pressed();
}
