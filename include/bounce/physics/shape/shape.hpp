#pragma once

#include "../../serialisation/json.hpp"

enum ShapeType {ST_CIRCLE, ST_RECT};
class CollisionShape {
public:
    double w, h;

    explicit CollisionShape(json j);
    CollisionShape(const CollisionShape &other) =default;

    [[nodiscard]] ShapeType get_type() const { return this->shape_type; }
    [[nodiscard]] bool is_circle() const { return this->shape_type == ST_CIRCLE; }
    [[nodiscard]] bool is_rectangle() const { return this->shape_type == ST_RECT; }
    static CollisionShape circle(double radius) { return CollisionShape(radius*2., radius*2., ST_CIRCLE); }
    static CollisionShape rectangle(double width, double height) { return CollisionShape(width, height, ST_RECT); }

    json serialise() const;
private:
    CollisionShape(double _w, double _h, ShapeType _shape): w(_w), h(_h), shape_type(_shape) {}

    ShapeType shape_type;

};