#pragma once

class PhysicsObject;
class Renderable {
public:
    Renderable() : _object(nullptr) {};

    virtual void draw() =0;

    void set_object(PhysicsObject *object) {this->_object = object; }
    PhysicsObject *get_object() const { return this->_object; }
private:
    PhysicsObject *_object;

};