#include <bounce/renderer/renderable/renderable.hpp>
#include <bounce/renderer/renderer.hpp>

Renderable::Renderable()
: Transform()
,   _colour(Colours::white)
,   _border_colour(Colours::white)
,   _aspect_ratio(1.0)
,   _angle(0.0)
,   _border_size(0.0)
,   _time_last_frame_advance(0.0)
,   _animation_period(0.1)
,   _size({1.0, 1.0})
,   _shader_name("default")
,   _texture(Renderer::get().get_texture("null"))
,   _current_texture_loop(Texture::default_loop)
,   _current_frame(0)
,   _visible(true)
,   _animated(false)
,   _is_x_flipped(false)
,   _is_y_flipped(false)
{
    this->add_tag("renderable");
}