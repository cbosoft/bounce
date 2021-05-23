#include <bounce/physics/collider/collider.hpp>

void Collider::on_physics_update()
{
    this->set_not_touching_anything();
}