#include <bounce/renderer/renderable/mesh/mesh.hpp>

MeshRenderable::MeshRenderable(json j)
:   Renderable(j)
{
    json points_json = j["points"];
    for (auto point_json : points_json) {
        double x = point_json[0], y = point_json[1];
        this->_points.push_back({x, y});
    }
    double x = j["anchor"][0], y = j["anchor"][1];
    this->_anchor = {x, y};
}

json MeshRenderable::serialise()
{
    json rv = Renderable::serialise();
    rv["type"] = "mesh renderable";
    json points;
    for (auto point : this->_points) {
        json point_json = {points[0], point[1]};
        points.push_back(point_json);
    }
    rv["points"] = points;
    rv["anchor"] = {this->_anchor[0], this->_anchor[1]};
    return rv;
}