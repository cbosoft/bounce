#pragma once
#include <string>

#include "../../colour/colour.hpp"
#include "../../transform/transform.hpp"

class Object;
class Renderable : public Transform {
public:
    Renderable();

    virtual void draw() const =0;

    bool is_fixed() const;
    void set_aspect_preserve_diagonal(double aspect);
    double get_aspect() const;
    void set_size(const arma::vec2 &size);
    const arma::vec2 &get_size() const;
    double get_angle() const;
    void set_angle(double angle);

    void set_object(Object *object);
    Object *get_object() const;

    const Colour &get_colour() const;
    void set_colour(const Colour &colour);
    const Colour &get_border_colour() const;
    void set_border_colour(const Colour &colour);
    void set_border_size(double border_size);
    double get_border_size() const;

    bool has_texture() const;
    const std::string &get_texture_name() const;
    void set_texture_name(const std::string &name);
    const std::string &get_shader_name() const;
    void set_shader_name(const std::string &name);

    bool get_visible() const;
    void set_visible(bool visibility);
    void hide();
    void show();

    void set_z(int z);
    int get_z() const;

    static bool z_sort(const Renderable *left, const Renderable *right) { return left->get_z() < right->get_z(); }
private:

    Colour _colour, _border_colour;
    double _aspect_ratio, _angle, _border_size;
    arma::vec2 _size;
    Object *_object;
    std::string texture_name, _shader_name;
    int _z;
    bool _visible;
};