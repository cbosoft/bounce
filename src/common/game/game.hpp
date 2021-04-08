#pragma once
#include <armadillo>
#include <vector>
#include <chrono>

#include "../transform/transform.hpp"
#include "../physics/engine/engine.hpp"
#include "../renderer/renderer.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::ratio<1, 1>> Duration;

class Game {
  public:
    explicit Game(int w=960, int h=960);
    ~Game();

    // Input
    void input_step();

    // Logic
    void logic_step();
    void add_object(PhysicsObject *obj);

    // Loop
    void run();
    void quit();

  private:
    bool should_quit;

    PhysicsEngine &physics;
    Renderer &renderer;

    Transform *camera;

    std::vector<PhysicsObject *> objects;

    Clock::time_point time_of_last_render, physics_epoch;
};
