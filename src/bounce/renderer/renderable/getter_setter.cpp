#include <bounce/renderer/renderable/renderable.hpp>
#include <bounce/renderer/renderer.hpp>
#include <bounce/object/object.hpp>

void Renderable::set_size(const arma::vec2 &size)
{
    this->_size = size;
}

arma::vec2 Renderable::get_size() const
{
    return this->_size*this->get_scale();
}

bool Renderable::has_texture() const
{
    return !this->_texture->is_null();
}

Texture *Renderable::get_texture() const
{
    return this->_texture;
}

void Renderable::set_texture_name(const std::string &name)
{
    this->_texture = Renderer::get().get_texture(name);
}

void Renderable::set_anim_loop(const std::string &name)
{
    if (this->_texture && name != this->_current_texture_loop_name) {
        this->_current_texture_loop = this->_texture->get_named_loop(name);
        this->_current_texture_loop_name = name;
        this->_has_completed_loop_once = false;
    }
}

void Renderable::set_animated(bool value)
{
    this->_animated = value;
}

void Renderable::set_animation_speed(double frame_per_second)
{
    this->_animation_period = 1./frame_per_second;
}

bool Renderable::has_completed_loop_once() const
{
    return this->_has_completed_loop_once;
}

const std::string &Renderable::get_current_anim_loop() const
{
    return this->_current_texture_loop_name;
}

void Renderable::x_flip(bool v) { this->_is_x_flipped = v; }
void Renderable::y_flip(bool v) { this->_is_y_flipped = v; }

const Colour &Renderable::get_colour() const
{
    return this->_colour;
}

void Renderable::set_colour(const Colour &colour)
{
    this->_colour = colour;
}

const Colour &Renderable::get_border_colour() const
{
    return this->_border_colour;
}

void Renderable::set_border_colour(const Colour &colour)
{
    this->_border_colour = colour;
}

double Renderable::get_border_size() const
{
    return this->_border_size*this->get_scale();
}

void Renderable::set_border_size(double border_size)
{
    this->_border_size = border_size;
}

void Renderable::set_visible(bool visibility)
{
    this->_visible = visibility;
}

bool Renderable::get_visible() const
{
    return this->_visible;
}

void Renderable::hide()
{
    this->set_visible(false);
}

void Renderable::show()
{
    this->set_visible(true);
}

void Renderable::set_shader_name(const std::string &name)
{
    this->_shader_name = name;
}

const std::string &Renderable::get_shader_name() const
{
    return this->_shader_name;
}

double Renderable::get_angle() const
{
    return this->_angle;
}

void Renderable::set_angle(double angle)
{
    this->_angle = angle;
}

void Renderable::set_frame(unsigned int frame)
{
    this->_current_frame = frame;
}

void Renderable::get_renderables(std::list<const Renderable *> &out) const
{
    if (this->is_active()) {
        out.push_back(this);
        Transform::get_renderables(out);
    }
}
