#include <bounce/game/game.hpp>
#include <bounce/logging/logger.hpp>

static bool game_unnamed = true;

/**
 * Get ref to Game singleton.
 *
 * If game is unnamed, this throws and exception. Use Game::ref(name) to set the game's name first. This is important to
 * keep the logs right.
 *
 * @return Reference to Game singleton.
 */
Game &Game::ref()
{
    static Game game;
    if (game_unnamed)
        throw std::runtime_error("Game is unnamed. Use Game::ref(name) first.");
    return game;
}

/**
 * Get Game ref, and set name of game. This is important for getting the logs right. This should be the first call in
 * your main function.
 *
 * @return Reference to Game singleton.
 */
Game &Game::ref(const std::string &name)
{
    if (!game_unnamed)
        throw std::runtime_error("Game is already named: cannot re-name!");
    game_unnamed = false;
    auto &game = Game::ref();
    game.set_name(name);
    Logger::ref().gen_unique_log_path();
    return game;
}
