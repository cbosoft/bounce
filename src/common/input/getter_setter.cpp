#include "manager.hpp"
#include "../renderer/renderer.hpp"
#include "../game/game.hpp"

InputContext *InputManager::get_context() const
{
    return this->_game->get_context();
}

GLFWwindow *InputManager::get_window() const
{
    return Renderer::get().get_window();
}

void InputManager::set_game(Game *game)
{
    this->_game = game;
}
