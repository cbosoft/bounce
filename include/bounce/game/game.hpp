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
#include "../serialisation/json.hpp"

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

    /* Perform first set up of Game object. */
    static Game &setup(const std::string &name);

    /* dtor */
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

    /* show/hide collision boxes */
    void show_colliders();
    void hide_colliders();
    [[nodiscard]] bool should_show_colliders() const;

    /* Get/set name of game */
    void set_name(const std::string &name);
    const std::string &get_name() const;

    /* Get path where settings should be stored. */
    std::filesystem::path get_settings_saves_path() const;

    /**
     * Get variable value from the Game state store.
     *
     * This is to be used for storing game state information - variables related to player actions and so on. This is
     * local to a "play" of a game - saved/loaded into individual files.
     *
     * \sa Game#set_state_value
     * \sa Game#get_settings_value
     * \sa Game#set_settings_value
     *
     * @param name The variable name to get.
     * @returns The value of the varaible.
     * */
    template<typename T>
    T get_state_value(const std::string &name)
    {
        return T(this->_state[name]);
    }

    /**
     * Set variable value in Game state store.
     *
     * This is to be used for storing game state information - variables related to player actions and so on. This is
     * local to a "play" of a game - saved/loaded into individual files.
     *
     * \sa Game#get_state_value
     * \sa Game#get_settings_value
     * \sa Game#set_settings_value
     *
     * @param name The variable name to set.
     * @param v The value of the variable.
     * */
    template<typename T>
    void set_state_value(const std::string &name, const T &v)
    {
        this->_state[name] = v;
    }

    /**
     * Get variable value in Game settings store.
     *
     * This is to be used for global settings - not related to game play. This is for things like graphics, controller,
     * audio settings and so on.
     *
     * \sa Game#get_state_value
     * \sa Game#set_state_value
     * \sa Game#set_settings_value
     *
     * @param name The variable name to set.
     * @returns The value of the variable.
     * */
    template<typename T>
    T get_settings_value(const std::string &name)
    {
        return T(this->_settings[name]);
    }

    /**
     * Set variable value in Game settings store.
     *
     * This is to be used for global settings - not related to game play. This is for things like graphics, controller,
     * audio settings and so on.
     *
     * \sa Game#get_state_value
     * \sa Game#set_state_value
     * \sa Game#get_settings_value
     *
     * @param name The variable name to set.
     * @param v The value of the variable.
     * */
    template<typename T>
    void set_settings_value(const std::string &name, const T &v)
    {
        this->_settings[name] = v;
    }

    /* Save game to save file in specified slot */
    void save_game(int slot);

    /* Load game from save file in specified slot */
    void load_game(int slot);

protected:
    Game();

private:
    /* Save settings to disk. */
    void save_settings();

    /* Load settings from disk. */
    void load_settings();

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

    json _settings, _state;
};
