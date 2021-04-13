#pragma once
#include <string>
#include <list>

#include "../renderable.hpp"
#include "../../renderer.hpp"
#include "../../font/font/font.hpp"

class TextRenderable : public Renderable {
public:
    TextRenderable(const std::string &text, const std::string &font_name, int height);

    void set_font_name(const std::string &font_name);
    const std::string &get_font_name() const;
    void set_font_size(int font_size);
    int get_font_size() const;
    void set_text(const std::string &text);
    const std::string &get_text() const;

    void draw() const override;

private:

    void refresh_font();

    Font *_font;
    std::string _text, _font_name;
    int _font_size;
};