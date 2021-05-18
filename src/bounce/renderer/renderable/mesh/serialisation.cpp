#include <bounce/renderer/renderable/mesh/mesh.hpp>

MeshRenderable::MeshRenderable(json j)
:   Renderable(j)
{
    json points_json = j["points"];
    for (auto point_json : points_json) {
        this->_points.push_back(jsonvec2(point_json));
    }
    this->_anchor = jsonvec2(j["anchor"]);
}

json MeshRenderable::serialise()
{
    json rv = Renderable::serialise();
    rv["type"] = "mesh renderable";
    json points;
    for (const auto &point : this->_points) {
        points.push_back(vec2json(point));
    }
    rv["points"] = points;
    rv["anchor"] = vec2json(this->_anchor);
    return rv;
}