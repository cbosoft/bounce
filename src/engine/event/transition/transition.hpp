#pragma once
#include <string>

#include "../event.hpp"

class PushSceneTransitionEvent : public ImmediateEvent {
public:
    PushSceneTransitionEvent(const std::string &scene_name);

    void run(Game *game) override;
private:
    std::string _target_scene_name;
};

class PopSceneTransitionEvent : public ImmediateEvent {
public:
    void run(Game *game) override;
};