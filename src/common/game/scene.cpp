#include "game.hpp"

void Game::add_scene(Scene *scene)
{
    this->scenes_by_name[scene->get_name()] = scene;
    if (this->get_active_scene() == nullptr) {
        this->scene_stack.push(scene);
        std::cerr << "active scene set to \"" << scene->get_name() << "\"" << std::endl;
    }
}

void Game::push_active_scene(const std::string &scene_name)
{
    auto it = this->scenes_by_name.find(scene_name);
    if (it != this->scenes_by_name.end()) {
        this->scene_stack.push(it->second);
        std::cerr << "active scene set to \"" << scene_name << "\"" << std::endl;
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
    return s;
}