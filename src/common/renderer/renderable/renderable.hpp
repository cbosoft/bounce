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
    double get_first_dimension() const { return this->size1; }
    double get_second_dimension() const { return this->size2; }
    void set_first_dimesion(double v) { this->size1 = v; }
    void set_second_dimension(double v) { this->size2 = v; }
    void set_x(double v) { this->x = v; }
    void set_y(double v) { this->y = v; }
    void set_object(PhysicsObject *object) {this->_object = object; }
    PhysicsObject *get_object() const { return this->_object; }

    bool has_texture() const { return !this->texture_name.empty(); }
    const std::string &get_texture_name() const { return this->texture_name; }
    void set_texture_name(const std::string &s) { this->texture_name = s; }

private:

    double x, y, size1, size2;
    PhysicsObject *_object;
    std::string texture_name;
};