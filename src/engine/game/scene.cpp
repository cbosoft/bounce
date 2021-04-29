#include "game.hpp"
#include "../logging/logger.hpp"

/**
 * Add Scene to Game. The Scene ptr is then owned by the Game.
 *
 * Registers scene with the game, so that it can be transitioned to. The Scene's name (returned by Scene#get_name) is
 * used as a unique key when storing the scene.
 *
 * \todo check for duplicate scenes before accepting addition of scene.
 *
 * @param scene Pointer to Scene to be added to Game.
 */
void Game::add_scene(Scene *scene)
{
    this->scenes_by_name[scene->get_name()] = scene;
    if (this->get_active_scene() == nullptr) {
        this->scene_stack.push(scene);
        Logger::ref() << LL_INFO << "Active scene set to \"" << scene->get_name() << "\".\n";
        scene->on_activate();
    }
}

/**
 * Make Scene with name \p scene_name the active scene.
 *
 * Active Scenes are stored on a stack - this pushes scene_name on to the top of the stack and thus becoming the active
 * Scene. A Scene can be pushed onto the stack multipled times. Scenes are removed from the active stack by
 * Game#pop_active_scene.
 *
 * If no Scene is found with name \p scene_name, then a warning is emitted and no Scene transition is made.
 *
 * @param scene_name
 */
void Game::push_active_scene(const std::string &scene_name)
{
    auto it = this->scenes_by_name.find(scene_name);
    if (it != this->scenes_by_name.end()) {
        Scene *scene = it->second;
        this->scene_stack.push(scene);
        Logger::ref() << LL_INFO << "Pushed scene. Active scene now \"" << scene_name << "\".\n";
        scene->on_activate();
    }
    else {
        Logger::ref() << LL_ERROR << "Scene with name\"" << scene_name << "\" not found.\n";
        throw std::runtime_error("Cannot set to requested scene; scene not found.");
    }
}

/**
 * @return the active Scene ptr - the Scene on top of the active stack.
 */
Scene *Game::get_active_scene() const
{
    if (this->scene_stack.empty()) {
        return nullptr;
    }
    return this->scene_stack.top();
}

/**
 * Remove the top Scene from the active scene.
 *
 * @return The Scene ptr removed from the active stack.
 */
Scene *Game::pop_active_scene()
{
    auto *s = this->scene_stack.top();
    this->scene_stack.pop();
    Scene *active = this->get_active_scene();
    if (active) {
        Logger::ref() << LL_INFO << "Popped active scene; active scene now \"" << active->get_name() << "\".\n";
        this->scene_stack.top()->on_activate();
    }
    else {
        Logger::ref() << LL_INFO << "Popped active scene; no scene active. Quitting.\n";
        this->quit();
    }
    return s;
}