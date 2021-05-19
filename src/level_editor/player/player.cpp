#include <iostream>
#include "player.hpp"

EditorPlayer::EditorPlayer(Transform *parent)
        :   Object(parent)
        ,   _dir{0.0}
        ,   _jump{false}
        ,   _fly_mode{false}
{
    this->set_shape(CollisionShape::rectangle(9, 9));
    auto *rbl = new RectangleMeshRenderable(10, 10);
    rbl->set_parent(this);
    this->set_bounciness(0.1);
    //this->set_friction(0.01);
}

void EditorPlayer::left_pressed() { this->_dir -= 1.; }
void EditorPlayer::left_released() { this->_dir += 1.; }
void EditorPlayer::right_pressed() { this->_dir += 1.; }
void EditorPlayer::right_released() { this->_dir -= 1.; }
void EditorPlayer::down_pressed() { this->_v_dir -= 1.; }
void EditorPlayer::down_released() { this->_v_dir += 1.; }
void EditorPlayer::up_pressed() { if (this->_fly_mode) { this->_v_dir += 1.;} else { this->_jump = this->_on_ground; } }
void EditorPlayer::up_released() { if (this->_fly_mode) {this->_v_dir -= 1.;} }

void EditorPlayer::on_update()
{

}

void EditorPlayer::on_collision(Object *other)
{
    (void) other;
    this->_on_ground = true;
}

void EditorPlayer::on_physics_update()
{
    if (this->_fly_mode) {
        arma::vec2 vel{this->_dir, this->_v_dir};
        vel *= 20.0;
        this->set_velocity(vel);
    }
    else {
        double fy = 0.0;
        if (this->_on_ground && this->_jump) {
            this->_on_ground = this->_jump = false;
            fy = 8e4;
        }

        //double spd_mult = this->_on_ground ? 1.0 : 0.01;
        this->add_force({this->_dir*4e2, fy});
        if (this->_dir == 0.0 && this->_on_ground) {
            this->set_velocity(this->get_velocity()*0.99);
        }

        this->_on_ground = false;
    }
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