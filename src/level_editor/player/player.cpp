#include <iostream>
#include "player.hpp"

EditorPlayer::EditorPlayer(Transform *parent)
        :   Object(parent)
        ,   _dir{0.0}
        ,   _jump{false}
{
    this->set_shape(CollisionShape::rectangle(9, 9));
    auto *rbl = new RectangleMeshRenderable(10, 10);
    rbl->set_parent(this);
    this->set_bounciness(0.1);
    this->set_friction(0.01);
}

void EditorPlayer::left_pressed() { this->_dir -= 1.; }
void EditorPlayer::left_released() { this->_dir += 1.; }
void EditorPlayer::right_pressed() { this->_dir += 1.; }
void EditorPlayer::right_released() { this->_dir -= 1.; }

void EditorPlayer::jump_pressed()
{
    this->_jump = this->_on_ground;
}

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
    double fy = 0.0;
    if (this->_on_ground && this->_jump) {
        this->_on_ground = this->_jump = false;
        fy = 1.7e4;
    }

    double spd_mult = this->_on_ground ? 1.0 : 0.05;
    this->add_force({this->_dir*100.0*spd_mult, fy});

    this->_on_ground = false;
}