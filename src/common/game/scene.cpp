#include "game.hpp"

void Game::add_scene(Scene *scene)
{
    this->scenes_by_name[scene->get_name()] = scene;
    if (this->get_active_scene() == nullptr) {
        this->scene_stack.push(scene);
        std::cerr << "active scene set to \"" << scene->get_name() << "\"" << std::endl;
        scene->on_activate();
    }
}

void Game::push_active_scene(const std::string &scene_name)
{
    auto it = this->scenes_by_name.find(scene_name);
    if (it != this->scenes_by_name.end()) {
        Scene *scene = it->second;
        this->scene_stack.push(scene);
        std::cerr << "active scene set to \"" << scene_name << "\"" << std::endl;
        scene->on_activate();
    }
    else {
        std::cerr << "scene with name\"" << scene_name << "\" not found." << std::endl;
        throw std::runtime_error("Cannot set to requested scene; scene not found.");
    }
}

const std::vector<PhysicsObject *> &Game::active_objects()
{
    auto *s = this->get_active_scene();
    if (s != nullptr) {
        return s->get_objects();
    }
    const static std::vector<PhysicsObject *> empty_list(0);
    return empty_list;
}

Scene *Game::get_active_scene() const
{
    if (this->scene_stack.empty()) {
        return nullptr;
    }
    return this->scene_stack.top();
}

Scene *Game::pop_active_scene()
{
    auto *s = this->scene_stack.top();
    this->scene_stack.pop();
    Scene *active = this->get_active_scene();
    if (active) {
        std::cerr << "Popped active scene; active scene now \"" << active->get_name() << "\"." << std::endl;
        this->scene_stack.top()->on_activate();
    }
    else {
        std::cerr << "Popped active scene; no scene active. Quitting." << std::endl;
        this->quit();
    }
    return s;
}