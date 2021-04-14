#include <iostream>
#include "renderer.hpp"

Renderer::Renderer()
: game(nullptr)
, aspect_ratio(1.0)
, window(nullptr)
, _screen_effect("default")
, vbuf(0)
, varr(0)
, fbo(0)
, txt(0)
, qbuf(0)
, qarr(0)
{
    // do nothing
}