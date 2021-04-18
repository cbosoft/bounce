#include "animated_mesh.hpp"

AnimatedMeshRenderable::AnimatedMeshRenderable(MeshRenderable *init)
:   MeshRenderable(init->points)
,   _movement_frames_left(0)
,   _original_scale(init->get_scale())
,   _scale_grad(0.0)
,   _original_points(init->points)
,   _target_points(init->points)
{

}