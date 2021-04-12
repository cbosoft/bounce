#pragma once
#include <string>

#include "../../colour/colour.hpp"
#include "../../transform/transform.hpp"

class PhysicsObject;
class Renderable : public Transform {
public:
    Renderable();

    virtual void draw() const =0;

    bool is_fixed() const;
    double get_scale() const;
    void set_scale(double scale);

    void set_object(PhysicsObject *object);
    PhysicsObject *get_object() const;

    const Colour &get_colour() const;
    void set_colour(const Colour &colour);

    bool has_texture() const;
    const std::string &get_texture_name() const;
    void set_texture_name(const std::string &name);

private:

    Colour _colour;
    double _scale;
    PhysicsObject *_object;
    std::string texture_name;
};