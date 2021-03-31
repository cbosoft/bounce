#include "game.hpp"

Game::Game(int w, int h)
  : w(w)
  , h(h)
  , should_quit(false)
  , win(nullptr)
  , renderer(nullptr)
{
  this->render_init();
}
