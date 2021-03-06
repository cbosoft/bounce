#pragma once
#include <string>
#include <list>
#include <armadillo>

#include "../renderable.hpp"
#include "../../renderer.hpp"
#include "../../font/font/font.hpp"

enum TextVAlign { VA_bottom, VA_centre, VA_top };
enum TextHAlign { HA_left, HA_centre, HA_right };

class TextRenderable : public Renderable {
public:
    explicit TextRenderable(json j);
    TextRenderable(const std::wstring &text, const std::string &font_name, int height, float width=-1.f);
    TextRenderable(const std::string &text, const std::string &font_name, int height, float width=-1.f);

    void set_alignment(TextHAlign h_align, TextVAlign v_align);
    void set_font_name(const std::string &font_name);
    const std::string &get_font_name() const;
    void set_font_size(int font_size);
    int get_font_size() const;
    void set_text(const std::wstring &text);
    void set_text(const std::string &text);
    const std::wstring &get_text() const;
    void set_typeset_width(float w);
    float get_typeset_width() const;
    void set_line_spacing(float line_spacing);
    float get_line_spacing() const;

    void draw() const override;
    arma::vec2 measure() const;

    json serialise() override;

private:

    void refresh_font();
    arma::vec2 aligned_origin() const;

    Font *_font;
    std::wstring _text;
    std::string _font_name;
    int _font_size;
    float _typesetting_width, _line_spacing;
    TextVAlign _v_align;
    TextHAlign _h_align;
};