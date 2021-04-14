#include <iostream>
#include "renderer.hpp"

Renderer::Renderer()
: game(nullptr)
, camera_angle(0.0)
, w(0)
, h(0)
, aspect_ratio(double(w)/double(h))
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