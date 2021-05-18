#include <bounce/renderer/renderable/renderable.hpp>
#include <bounce/serialisation/json.hpp>
#include <bounce/renderer/renderer.hpp>

Renderable::Renderable(json j)
:   Transform(j)
,   _colour(Colours::white)
,   _border_colour(Colours::white)
{
    this->_angle = j["angle"];
    this->_size = jsonvec2(j["size"]);
    this->_shader_name = j["shader"];
    this->_texture = Renderer::get().get_texture(j["texture"]);
    this->_visible = j["visible"];
    this->_colour = Colour::from_json(j["colour"]);
    this->_border_colour = Colour::from_json(j["border colour"]);
    this->_border_size = j["border size"];
}

json Renderable::serialise()
{
    json rv = Transform::serialise();
    rv["type"] = "renderable";
    rv["angle"] = this->_angle;
    rv["size"] = vec2json(this->_size);
    rv["shader"] = this->_shader_name;
    rv["texture"] = this->_texture->get_name();
    rv["visible"] = this->_visible;
    rv["colour"] = this->_colour.serialise();
    rv["border colour"] = this->_border_colour.serialise();
    rv["border size"] = this->_border_size;
    return rv;
}