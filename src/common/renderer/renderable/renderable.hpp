#pragma once
#include <string>

class PhysicsObject;
class Renderable {
public:
    Renderable();

    virtual void draw() const =0;

    bool is_fixed() const;
    double get_x() const;
    double get_y() const;
    double get_scale() const;
    void set_scale(double v);
    void set_x(double v);
    void set_y(double v);
    void set_object(PhysicsObject *object);
    PhysicsObject *get_object() const;

    bool has_texture() const;
    const std::string &get_texture_name() const;
    void set_texture_name(const std::string &name);

private:

    double x, y, s;
    PhysicsObject *_object;
    std::string texture_name;
};