#include <bounce/renderer/renderer.hpp>

/**
 * Construct Renderer. Set most things to zero. Create an empty fallback Texture called "null".
 *
 * This creates the Renderer object, but it still needs to be initialised by calling the Renderer#init method. This is
 * done in Game#setup.
 */
Renderer::Renderer()
: game(nullptr)
, window_size({0, 0})
, _window_scale({1, 1})
, aspect_ratio(1.0)
, window(nullptr)
, _screen_effect("default")
, vbuf(0)
, varr(0)
, fbo(0)
, txt(0)
, qbuf(0)
, qarr(0)
, _max_fps(1)
, _min_mspf(1)
, _actual_fps(1)
{
    this->set_max_fps(60);
    this->textures["null"] = new Texture(nullptr);
}