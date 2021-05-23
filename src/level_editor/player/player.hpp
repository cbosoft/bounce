#pragma once

#include <bounce/bounce.hpp>

enum AnimState { AS_IDLE, AS_MOVE, AS_FALL, AS_LAND };

class EditorPlayer final : public Rigidbody {
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

    void on_update() override;
    void on_physics_update() override;

private:

    void update_anim_loop();

    double _dir, _v_dir;
    bool _jump, _fly_mode, _was_falling;
    RectangleMeshRenderable *_sprite, *_left, *_top, *_right, *_bottom;
    AnimState _anim_state;
};