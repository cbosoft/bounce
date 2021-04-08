#pragma once
#include <armadillo>
#include <vector>

#include "../transform/transform.hpp"
#include "../physics/engine/engine.hpp"
#include "../renderer/renderer.hpp"
#include "../input/manager.hpp"
#include "../input/context/context.hpp"

class Game {
  public:
    explicit Game(int w=960, int h=960);
    ~Game();

    // Logic
    void logic_step();
    void add_object(PhysicsObject *obj);
    void set_player(PhysicsObject *player);
    PhysicsObject *get_player() const;

    // Loop
    void run();

    // Actions
    void quit();
    InputContext *get_context() const;

  private:
    bool should_quit;

    PhysicsEngine &physics;
    Renderer &renderer;
    InputContext *context;

    Transform *camera;
    PhysicsObject *_player;

    std::vector<PhysicsObject *> objects;
};
