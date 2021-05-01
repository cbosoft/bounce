#include "scene.hpp"

DemoPlatformer::DemoPlatformer()
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

    this->player = new DemoPlatformerPlayer(this);
    this->player->set_position({0, -45});

    auto *gravity = new UnboundedLinearForceField(0, 0, 0, -10);
    this->add_field(gravity);

    this->get_active_camera()->set_parent(this->player);
}

void DemoPlatformer::on_activate()
{
    Game::ref().show_colliders();
    PhysicsEngine::ref().set_timescale(3.0);
    Renderer::get().set_screen_effect("1bit");
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
