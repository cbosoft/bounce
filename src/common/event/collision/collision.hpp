#pragma once

#include "../event.hpp"

class Object;
class CollisionEvent : public ImmediateEvent {
public:
    CollisionEvent(Object *a, Object *b);

    void run(Game *game) override;

    Object *_a, *_b;
};