#pragma once
#include <string>

class PhysicsObject;
class Renderable {
public:
    Renderable() : _object(nullptr) {};

    virtual void draw() const =0;

    bool is_fixed() const { return this->_object == nullptr; }
    double get_x() const { return this->x; }
    double get_y() const { return this->y; }
    double get_scale() const { return this->s; }
    void set_scale(double v) { this->s = v; }
    void set_x(double v) { this->x = v; }
    void set_y(double v) { this->y = v; }
    void set_object(PhysicsObject *object) {this->_object = object; }
    PhysicsObject *get_object() const { return this->_object; }

    bool has_texture() const { return !this->texture_name.empty(); }
    const std::string &get_texture_name() const { return this->texture_name; }
    void set_texture_name(const std::string &name) { this->texture_name = name; }

private:

    double x, y, s;
    PhysicsObject *_object;
    std::string texture_name;
};