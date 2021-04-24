#pragma once

#include "../event.hpp"
#include "../../transform/transform.hpp"

class TransformDestroyEvent : public ImmediateEvent
{
public:
    explicit TransformDestroyEvent(Transform *to_be_destroyed);

    void run(Game *game) override;

    Transform *_to_be_destroyed;
};