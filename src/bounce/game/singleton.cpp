#include <bounce/game/game.hpp>
#include <bounce/logging/logger.hpp>

static bool game_unnamed = true;

/**
 * Get ref to Game singleton.
 *
 * If game is not set up, will raise exception. Run Game::setup() first.
 *
 * @return Reference to Game singleton.
 */
Game &Game::ref()
{
    static Game game;
    if (game_unnamed)
        throw std::runtime_error("Game is not yet set up. Use Game::setup(...) first.");
    return game;
}

/**
 * Do initial setup of Game, and return ref to created object. This should be the first call in
 * your main function.
 *
 * @return Reference to Game singleton.
 */
Game &Game::setup(const std::string &name)
{
    if (!game_unnamed)
        throw std::runtime_error("Game is already set up: cannot set up again!");
    game_unnamed = false;
    auto &game = Game::ref();
    game.set_name(name);
    game.load_settings();
    auto res = game.get_settings_value<json>("graphics", "resolution");
    int w = res["w"], h = res["h"];
    Renderer::get().init(&game, w, h, name);
    Renderer::get().set_window_name(name);
    Logger::ref().gen_unique_log_path();

    return game;
}
