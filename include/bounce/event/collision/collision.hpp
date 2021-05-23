#pragma once

#include "../event.hpp"

class Collider;
class CollisionEvent : public ImmediateEvent {
public:
    CollisionEvent(Collider *a, Collider *b);

    void run(Game *game) override;

    Collider *_a, *_b;
};