#pragma once


class CollisionShape {
public:
    double w, h;

    [[nodiscard]] bool is_circle() const { return this->shape_type == ST_CIRCLE; }
    [[nodiscard]] bool is_rectangle() const { return this->shape_type == ST_RECT; }
    static CollisionShape circle(double radius) { return CollisionShape(radius, radius, ST_CIRCLE); }
    static CollisionShape rectangle(double width, double height) { return CollisionShape(width, height, ST_RECT); }

private:
    enum ShapeType {ST_CIRCLE, ST_RECT};
    CollisionShape(double _w, double _h, ShapeType _shape): w(_w), h(_h), shape_type(_shape) {}

    ShapeType shape_type;

};