#include <iostream>
#include "player.hpp"

DemoPlatformerPlayer::DemoPlatformerPlayer(Transform *parent)
        :   Object(parent, {0, 0}, false)
        ,   _dir{0.0}
        ,   _jump{false}
{
    this->set_shape(CollisionShape::rectangle(1, 1));
    this->set_bounciness(0.1);
    this->set_friction(0.01);
}

void DemoPlatformerPlayer::left_pressed() { this->_dir -= 1.; }
void DemoPlatformerPlayer::left_released() { this->_dir += 1.; }
void DemoPlatformerPlayer::right_pressed() { this->_dir += 1.; }
void DemoPlatformerPlayer::right_released() { this->_dir -= 1.; }

void DemoPlatformerPlayer::jump_pressed()
{
    this->_jump = true;
    std::cerr << "jump!" << std::endl;
}

void DemoPlatformerPlayer::on_update()
{

}

void DemoPlatformerPlayer::on_collision(Object *other)
{
    (void) other;
    this->_on_ground = true;
}

void DemoPlatformerPlayer::on_physics_update()
{
    double fy = 0.0;
    if (this->_on_ground && this->_jump) {
        this->_on_ground = this->_jump = false;
        fy = 1.5e4;
    }

    double spd_mult = this->_on_ground ? 1.0 : 0.1;
    this->add_force({this->_dir*100.0*spd_mult, fy});

    this->_on_ground = false;
}