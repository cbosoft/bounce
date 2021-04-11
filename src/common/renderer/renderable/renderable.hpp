#pragma once
#include <string>

class PhysicsObject;
class Renderable {
public:
    Renderable() : _object(nullptr) {};

    virtual void draw() const =0;

    void set_object(PhysicsObject *object) {this->_object = object; }
    PhysicsObject *get_object() const { return this->_object; }

    bool has_texture() const { return !this->texture_name.empty(); }
    const std::string &get_texture_name() const { return this->texture_name; }
    void set_texture_name(const std::string &s) { this->texture_name = s; }

private:

    PhysicsObject *_object;
    std::string texture_name;
};