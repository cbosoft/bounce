#include "game.hpp"

Game &Game::ref()
{
    static Game game;
    return game;
}