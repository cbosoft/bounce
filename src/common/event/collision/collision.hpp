#pragma once

#include "../event.hpp"

class PhysicsObject;
class CollisionEvent : public ImmediateEvent {
public:
    CollisionEvent(PhysicsObject *a, PhysicsObject *b);

    void run(Game *game) override;

    PhysicsObject *_a, *_b;
};