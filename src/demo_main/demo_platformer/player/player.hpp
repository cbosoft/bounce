#pragma once

#include "../../../engine/bounce.hpp"

class DemoPlatformerPlayer final : public Object{
public:
    explicit DemoPlatformerPlayer(Transform *parent);

    void left_pressed();
    void left_released();
    void right_pressed();
    void right_released();
    void jump_pressed();

    void on_collision(Object *other) override;
    void on_update() override;
    void on_physics_update() override;

private:
    double _dir;
    bool _jump, _on_ground;
};