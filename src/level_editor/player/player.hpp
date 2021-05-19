#pragma once

#include <bounce/bounce.hpp>

class EditorPlayer final : public Object{
public:
    explicit EditorPlayer(Transform *parent);

    void left_pressed();
    void left_released();
    void right_pressed();
    void right_released();
    void down_pressed();
    void down_released();
    void up_pressed();
    void up_released();

    void set_fly_mode(bool value);
    void toggle_fly_mode();

    void on_collision(Object *other) override;
    void on_update() override;
    void on_physics_update() override;

private:
    double _dir, _v_dir;
    bool _jump, _on_ground, _fly_mode;
};