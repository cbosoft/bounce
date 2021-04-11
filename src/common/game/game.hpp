#pragma once
#include <armadillo>
#include <vector>
#include <stack>

#include "../transform/transform.hpp"
#include "../physics/engine/engine.hpp"
#include "../renderer/renderer.hpp"
#include "../input/manager.hpp"
#include "../scene/scene.hpp"

class Game {
  public:
    explicit Game(int w=960, int h=960);
    ~Game();

    // Logic
    void logic_step();
    void push_active_scene(const std::string &scene_name);
    Scene *pop_active_scene();
    void add_scene(Scene *scene);
    void add_object(PhysicsObject *object);
    const std::vector<PhysicsObject *> &active_objects();

    // Loop
    void run();

    // Actions
    void quit();
    InputContext *get_context() const;

  private:
    Scene *get_active_scene() const;
    bool should_quit;

    PhysicsEngine &physics;
    Renderer &renderer;

    std::stack<Scene *> scene_stack;

    std::vector<PhysicsObject *> all_objects;
    std::map<std::string, Scene *> scenes_by_name;
};
