#include "game.hpp"
#include "../input/context/contexts.hpp"

Game::Game(int w, int h)
  : should_quit(false)
  , physics(PhysicsEngine::engine())
  , renderer(Renderer::init(w, h, "bounce"))
  , context(nullptr)
{
    this->camera = &this->renderer.camera_transform;
    this->context = new DefaultContext(this);
}
