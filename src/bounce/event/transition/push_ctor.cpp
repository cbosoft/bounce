#include <bounce/event/transition/transition.hpp>

PushSceneTransitionEvent::PushSceneTransitionEvent(const std::string &scene_name)
: _target_scene_name(scene_name)
{
    // do nothing
}