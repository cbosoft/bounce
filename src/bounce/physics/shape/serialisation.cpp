#include <bounce/physics/shape/shape.hpp>

CollisionShape::CollisionShape(json j)
{
    this->w = j["w"];
    this->h = j["h"];
    std::string shape_type_str = j["shape type"];
    if (shape_type_str == "rectangle") {
        this->shape_type = ST_RECT;
    }
    else {
        this->shape_type = ST_CIRCLE;
    }
}

json CollisionShape::serialise() const
{
    json rv;
    rv["type"] = "collision shape";
    rv["w"] = this->w;
    rv["h"] = this->h;
    rv["shape type"] = this->shape_type == ST_RECT ? "rectangle" : "circle";
    return rv;
}