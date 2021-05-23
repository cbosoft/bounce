#include <iostream>
#include "player.hpp"

EditorPlayer::EditorPlayer(Transform *parent)
        :   Rigidbody(parent)
        ,   _dir{0.0}
        ,   _jump{false}
        ,   _fly_mode{false}
{
    this->set_shape_rectangle(9, 9);
    this->_sprite = new RectangleMeshRenderable(16, 16);
    this->_sprite->set_relative_position({0, 3});
    this->_sprite->set_parent(this);
    this->_sprite->set_texture_name("sword-dude");
    this->_sprite->set_anim_loop("IDLE");
    this->_sprite->set_animated(true);
    this->_sprite->set_animation_speed(10);
    this->set_bounciness(0.1);
    //this->set_friction(0.01);

    this->_left = new RectangleMeshRenderable(3, 3);
    this->_left->set_parent(this);
    this->_left->set_relative_position({-5, 0});
    this->_left->hide();

    this->_right = new RectangleMeshRenderable(3, 3);
    this->_right->set_parent(this);
    this->_right->set_relative_position({5, 0});
    this->_right->hide();

    this->_top = new RectangleMeshRenderable(3, 3);
    this->_top->set_parent(this);
    this->_top->set_relative_position({0, 5});
    this->_top->hide();

    this->_bottom = new RectangleMeshRenderable(3, 3);
    this->_bottom->set_parent(this);
    this->_bottom->set_relative_position({0, -5});
    this->_bottom->hide();

    this->_anim_state = AS_IDLE;
}

void EditorPlayer::left_pressed() { this->_dir -= 1.; }
void EditorPlayer::left_released() { this->_dir += 1.; }
void EditorPlayer::right_pressed() { this->_dir += 1.; }
void EditorPlayer::right_released() { this->_dir -= 1.; }
void EditorPlayer::down_pressed() { this->_v_dir -= 1.; }
void EditorPlayer::down_released() { this->_v_dir += 1.; }
void EditorPlayer::up_pressed() { if (this->_fly_mode) { this->_v_dir += 1.;} else { this->_jump = this->is_touching_bottom(); } }
void EditorPlayer::up_released() { if (this->_fly_mode) {this->_v_dir -= 1.;} }

void EditorPlayer::on_update()
{
    if (this->is_touching_left()) { this->_left->show(); } else { this->_left->hide(); }
    if (this->is_touching_right()) { this->_right->show(); } else { this->_right->hide(); }
    if (this->is_touching_top()) { this->_top->show(); } else { this->_top->hide(); }
    if (this->is_touching_bottom()) { this->_bottom->show(); } else { this->_bottom->hide(); }

    this->update_anim_loop();

    if (this->_dir < -0.1)
        this->_sprite->x_flip(true);

    if (this->_dir > 0.1)
        this->_sprite->x_flip(false);
}

void EditorPlayer::update_anim_loop()
{
    switch (this->_anim_state) {
        case AS_IDLE:
            if (this->is_touching_bottom()) {
                if (std::abs(this->_dir) > 0.1) {
                    this->_anim_state = AS_MOVE;
                }
            }
            else {
                this->_anim_state = AS_FALL;
            }
            break;

        case AS_FALL:
            if (this->is_touching_bottom()) {
                this->_anim_state = AS_LAND;
            }
            break;

        case AS_MOVE:
            if (std::abs(this->_dir) < 0.1) {
                this->_anim_state = AS_IDLE;
            }
            if (!this->is_touching_bottom()) {
                this->_anim_state = AS_IDLE;
            }
            break;

        case AS_LAND:
            if (this->_sprite->has_completed_loop_once()) {
                this->_anim_state = AS_IDLE;
            }

    }
    (void) _was_falling;
    std::string loop_name;
    switch (this->_anim_state) {
        case AS_IDLE: loop_name = "IDLE"; break;
        case AS_MOVE: loop_name = "MOVE"; break;
        case AS_FALL: loop_name = "FALL"; break;
        case AS_LAND: loop_name = "LAND"; break;
    }
    this->_sprite->set_anim_loop(loop_name);
}

void EditorPlayer::on_physics_update()
{
    constexpr double maxvel = 100.;
    if (this->_fly_mode) {
        arma::vec2 vel{this->_dir, this->_v_dir};
        vel *= maxvel;
        this->set_velocity(vel);
    }
    else {
        double fy = 0.0, spd_mult = 1.0;
        if (this->is_touching_bottom()) {
            if (std::abs(this->_dir) < 0.1) {
                this->set_velocity(this->get_velocity() * 0.99);
            }

            if (this->_jump) {
                fy = 8.5e4;
                //this->set_velocity(this->get_velocity() + arma::vec2{0, 10});
                this->_jump = false;
            }
            spd_mult = 0.5;
        }


        this->add_force({this->_dir*spd_mult*4e2, fy});

        arma::vec2 vel = this->get_velocity();
        if (vel[0] < -maxvel) vel[0] = -maxvel;
        if (vel[0] > maxvel)  vel[0] = maxvel;
        this->set_velocity(vel);
    }

    Rigidbody::on_physics_update();
}

void EditorPlayer::set_fly_mode(bool value)
{
    this->_fly_mode = value;
    this->set_fixed(value);
}

void EditorPlayer::toggle_fly_mode()
{
    this->set_fly_mode(!this->_fly_mode);
}