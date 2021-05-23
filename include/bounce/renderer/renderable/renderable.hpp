#pragma once
#include <string>

#include "../../colour/colour.hpp"
#include "../../transform/transform.hpp"
#include "../texture/texture.hpp"

class Renderable : public Transform {
public:
    Renderable();
    explicit Renderable(json s);

    virtual void draw() const =0;

    void set_aspect_preserve_diagonal(double aspect);
    double get_aspect() const;
    void set_size(const arma::vec2 &size);
    arma::vec2 get_size() const;
    double get_angle() const;
    void set_angle(double angle);

    const Colour &get_colour() const;
    void set_colour(const Colour &colour);
    const Colour &get_border_colour() const;
    void set_border_colour(const Colour &colour);
    void set_border_size(double border_size);
    double get_border_size() const;

    bool has_texture() const;
    Texture *get_texture() const;
    void set_texture_name(const std::string &name);
    const std::string &get_shader_name() const;
    void set_shader_name(const std::string &name);
    void set_anim_loop(const std::string &name);
    [[nodiscard]] const std::string &get_current_anim_loop() const;
    void set_animated(bool value);
    void set_animation_speed(double frame_per_second);
    [[nodiscard]] bool has_completed_loop_once() const;
    void x_flip(bool v);
    void y_flip(bool v);

    void on_update() override;

    void set_frame(unsigned int frame);

    void set_target(Texture *texture);

    bool get_visible() const;
    void set_visible(bool visibility);
    void hide();
    void show();

    static bool z_sort(const Renderable *left, const Renderable *right) { return left->get_z() < right->get_z(); }

    void get_renderables(std::list<const Renderable *> &out) const override;

    json serialise() override;

protected:
    Colour _colour, _border_colour;
    double _aspect_ratio, _angle, _border_size, _time_last_frame_advance, _animation_period;
    arma::vec2 _size;
    std::string _shader_name, _current_texture_loop_name;
    Texture *_texture;
    TextureAnimLoop _current_texture_loop;
    unsigned int _current_frame;
    bool _visible, _animated, _has_completed_loop_once, _is_x_flipped, _is_y_flipped;
    GLuint _target;
};