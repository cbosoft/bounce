#include <bounce/renderer/renderable/mesh/animated_mesh/animated_mesh.hpp>

AnimatedMeshRenderable::AnimatedMeshRenderable(MeshRenderable *init)
:   MeshRenderable(init->_points)
,   _movement_frames_left(0)
,   _original_angle(init->get_angle())
,   _angle_grad(0.0)
,   _original_size(init->get_size())
,   _scale_grad({0.0, 0.0})
,   _original_pos(init->get_position())
,   _position_grad({0.0, 0.0})
,   _original_points(init->_points)
,   _target_points(init->_points)
,   _animate_position(false)
{

}

void AnimatedMeshRenderable::set_animate_position(bool v)
{
    this->_animate_position = v;
}