#include "manager.hpp"
#include "../renderer/renderer.hpp"
#include "../game/game.hpp"

InputContext *InputManager::get_context() const
{
    return Game::ref().get_context();
}

GLFWwindow *InputManager::get_window() const
{
    return Renderer::get().get_window();
}