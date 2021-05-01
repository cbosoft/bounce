#include <bounce/game/game.hpp>
#include <bounce/version/version.hpp>
#include <bounce/logging/logger.hpp>

/**
 * Game object constructor. Initialises physics engine (if not already) and the renderer.
 *
 * Renderer initialisation sets the initial window size - 1280x960 here.
 *
 * \todo Don't hard-code the initial window size - load from saved settings
 */
Game::Game()
  : should_quit(false)
  , _visible_colliders(false)
  , physics(PhysicsEngine::ref())
  , renderer(Renderer::get())
  , sound(SoundManager::ref())
  , _name("bounce")
{
    Logger::ref() << LL_INFO << VersionInfo::version_string();
}
