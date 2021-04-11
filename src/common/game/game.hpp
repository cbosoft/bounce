#pragma once
#include <armadillo>
#include <vector>

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
    void set_active_scene(const std::string &scene_name);
    void add_scene(Scene *scene);
    void add_object(PhysicsObject *object);
    const std::vector<PhysicsObject *> &active_objects();

    // Loop
    void run();

    // Actions
    void quit();
    InputContext *get_context() const;

  private:
    bool should_quit;

    PhysicsEngine &physics;
    Renderer &renderer;

    Scene *active_scene;

    std::vector<PhysicsObject *> all_objects;
    std::map<std::string, Scene *> scenes_by_name;
};
