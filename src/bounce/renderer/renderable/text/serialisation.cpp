#include <bounce/renderer/renderable/text/text.hpp>

TextRenderable::TextRenderable(json j)
:   Renderable(j)
{
    this->_font = nullptr;
    this->_font_name = j["font name"];
    std::string stext = j["text"];
    this->_text = std::wstring(stext.begin(), stext.end());
    this->_font_size = j["font size"];
    this->_typesetting_width = j["typesetting width"];
    this->_line_spacing = j["line spacing"];

    json va = j["vertical align"];
    this->_v_align = VA_centre;
    if (!va.is_null()) {
        std::string salign = va;
        if (salign == "top") this->_v_align = VA_top;
        else if (salign == "centre") this->_v_align = VA_centre;
        else if (salign == "bottom") this->_v_align = VA_bottom;
    }

    json ha = j["horizontal align"];
    this->_h_align = HA_centre;
    if (!ha.is_null()) {
        std::string salign = ha;
        if (salign == "left") this->_h_align = HA_left;
        else if (salign == "centre") this->_h_align = HA_centre;
        else if (salign == "right") this->_h_align = HA_right;
    }
}

json TextRenderable::serialise()
{
    json rv = Renderable::serialise();
    rv["type"] = "text renderable";
    rv["font name"] = this->_font_name;
    rv["text"] = this->_text;
    rv["font size"] = this->_font_size;
    rv["typesetting width"] = this->_typesetting_width;
    rv["line spacing"] = this->_line_spacing;

    switch (this->_v_align) {
        case VA_bottom: rv["vertical align"] = "bottom"; break;
        case VA_centre: rv["vertical align"] = "centre"; break;
        case VA_top:    rv["vertical align"] = "top";    break;
    }

    switch (this->_h_align) {
        case HA_left:   rv["horizontal align"] = "left";   break;
        case HA_centre: rv["horizontal align"] = "centre"; break;
        case HA_right:  rv["horizontal align"] = "right";  break;
    }

    return rv;
}