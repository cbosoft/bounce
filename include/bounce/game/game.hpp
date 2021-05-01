#pragma once
#include <armadillo>
#include <vector>
#include <list>
#include <stack>

#include "../transform/transform.hpp"
#include "../physics/engine/engine.hpp"
#include "../renderer/renderer.hpp"
#include "../input/manager.hpp"
#include "../scene/scene.hpp"
#include "../event/event.hpp"
#include "../sound/manager/manager.hpp"

/**
 * Game - singleton object managing the general running of the game.
 *
 * The Game manages Events and Scenes. In addition, the Game singleton typically is where the initialisation of the
 * PhysicsEngine and the Renderer is done.
 *
 * \todo Serialisation, saving, settings, game state
 */
class Game {
  public:
    /* Get ref to singleton. */
    static Game &ref();
    ~Game();

    /* Logic step - where events are processed. */
    void logic_step();

    /* Register a new event to be processed when ready. The Event ptr is owned by the game. */
    void add_event(Event *event);

    /* Put transform into the graveyard - when suitable, it will be deleted. */
    void add_to_graveyard(Transform *transform);

    /* Push named scene onto active stack - making it the new active scene.  */
    void push_active_scene(const std::string &scene_name);

    /* Pop currently active scene from stack. */
    Scene *pop_active_scene();

    /* Return the current scene on top of the stack - the active scene.*/
    [[nodiscard]] Scene *get_active_scene() const;

    /* Get a list of scenes which need rendering. */
    [[nodiscard]] std::list<Scene *>get_scenes_to_be_rendered() const;

    /* Add a scene to the game. The Scene ptr is owned by the game.*/
    void add_scene(Scene *scene);

    /* Run the game. */
    void run();

    /* Quit the game - stop running, exit the game. */
    void quit();

    /* Returns the object currently accepting input - this is the active scene by another name. */
    [[nodiscard]] InputContext *get_context() const;

    void show_colliders();
    void hide_colliders();
    bool should_show_colliders() const;
    void set_name(const std::string &name);
    const std::string &get_name() const;

protected:
    Game();

private:
    bool should_quit, _visible_colliders;

    PhysicsEngine &physics;
    Renderer &renderer;
    SoundManager &sound;

    std::vector<Scene *> scene_stack;
    std::list<Event *> events;
    std::vector<Object *> all_objects;
    std::map<std::string, Scene *> scenes_by_name;
    std::list<Transform *> graveyard;

    std::string _name;
};
