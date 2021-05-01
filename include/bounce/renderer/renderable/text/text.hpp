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
    TextRenderable(const std::wstring &text, const std::string &font_name, int height);
    TextRenderable(const std::string &text, const std::string &font_name, int height);

    void set_alignment(TextHAlign h_align, TextVAlign v_align);
    void set_font_name(const std::string &font_name);
    const std::string &get_font_name() const;
    void set_font_size(int font_size);
    int get_font_size() const;
    void set_text(const std::wstring &text);
    void set_text(const std::string &text);
    const std::wstring &get_text() const;

    void draw() const override;
    arma::vec2 measure() const;

private:

    void refresh_font();
    arma::vec2 aligned_origin() const;

    Font *_font;
    std::wstring _text;
    std::string _font_name;
    int _font_size;
    TextVAlign _v_align;
    TextHAlign _h_align;
};