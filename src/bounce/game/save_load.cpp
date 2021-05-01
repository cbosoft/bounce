#include <bounce/game/game.hpp>
#include <bounce/logging/logger.hpp>

#ifndef SAVE_SETTINGS_DIR
#define SAVE_SETTINGS_DIR "HOME"
#endif

/**
 *
 * Settings and saves are stored in json files. These are in a location which depends on the operating system:
 * - Unix-like: $HOME/.${GAME::get_name()}/<files go here>
 * - Windows: %LOCALAPPDATA%/${GAME::get_name()}/<files go here>
 *
 * @return The path to the directory in which settings and saves should be stored.
 */
std::filesystem::path Game::get_settings_saves_path() const
{
    std::filesystem::path p = std::getenv(SAVE_SETTINGS_DIR);
    p /= this->get_name();
    if (!std::filesystem::exists(p)) {
        std::filesystem::create_directory(p);
    }
    return p;
}

/**
 * Save settings to disk.
 *
 * Settings are stored in a json file, location depending on the operating system.
 *
 * \sa Game#get_settings_saves_path
 */
void Game::save_settings()
{
    auto p = this->get_settings_saves_path();
    p /= "settings.json";
    std::ofstream ofs(p);
    ofs << this->_settings;
}

/**
 * Load settings from disk.
 *
 * Settings are stored in a json file, location depending on the operating system.
 *
 * \sa Game#get_settings_saves_path
 */
void Game::load_settings()
{
    // load settings from disk
    auto p = this->get_settings_saves_path();
    p /= "settings.json";
    if (std::filesystem::exists(p)) {
        std::ifstream ifs(p);
        ifs >> this->_settings;
        Logger::ref() << LL_INFO << "Settings loaded from " << p << "\n";
    }
    else {
        Logger::ref() << LL_WARN << "Could not load game settings from " << p << "\n";
        Logger::ref() << LL_WARN << "Reverting to default\n";
        this->_settings = {
                {"graphics", {
                    {"resolution", {
                        {"w", 1280},
                        {"h", 960}
                    }}
                }}
        };
        this->save_settings();
    }
}

/**
 * Save game to disk, in slot \p slot.
 *
 * Game state is stored in a json file, location depending on the operating system.
 *
 * \sa Game#get_settings_saves_path
 */
void Game::save_game(int slot)
{
    auto p = this->get_settings_saves_path();
    std::stringstream ss;
    ss << "save_" << slot << ".json";
    p /= ss.str();
    std::ofstream ofs(p);
    ofs << this->_state;
    Logger::ref() << LL_INFO << "Game state saved to " << p << "\n";
}

/**
 * Load game to disk, in slot \p slot.
 *
 * Game state is stored in a json file, location depending on the operating system.
 *
 * \sa Game#get_settings_saves_path
 */
void Game::load_game(int slot)
{
    auto p = this->get_settings_saves_path();
    std::stringstream ss;
    ss << "save_" << slot << ".json";
    p /= ss.str();
    if (std::filesystem::exists(p)) {
        std::ifstream ifs(p);
        ifs >> this->_state;
        Logger::ref() << LL_INFO << "Game state loaded from " << p << "\n";
    }
    else {
        Logger::ref() << LL_WARN << "Could not load game in" << p << "\n";
        throw std::runtime_error("could not load requested save game - does not exist!");
    }
}
