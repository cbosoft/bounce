#include "game.hpp"

void Game::add_scene(Scene *scene)
{
    this->scenes_by_name[scene->get_name()] = scene;
    if (this->active_scene == nullptr) {
        this->active_scene = scene;
        std::cerr << "active scene set to \"" << scene->get_name() << "\"" << std::endl;
    }
}

void Game::set_active_scene(const std::string &scene_name)
{
    auto it = this->scenes_by_name.find(scene_name);
    if (it != this->scenes_by_name.end()) {
        this->active_scene = it->second;
        std::cerr << "active scene set to \"" << scene_name << "\"" << std::endl;
    }
    else {
        std::cerr << "scene with name\"" << scene_name << "\" not found." << std::endl;
        throw std::runtime_error("Cannot set to requested scene; scene not found.");
    }
}

const std::vector<PhysicsObject *> &Game::active_objects()
{
    if (this->active_scene != nullptr) {
        return this->active_scene->get_objects();
    }
    const static std::vector<PhysicsObject *> empty_list(0);
    return empty_list;
}