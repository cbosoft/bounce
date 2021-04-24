#pragma once
#include <map>
#include <string>
#include <armadillo>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int texture_id;
    float w;
    float h;
    float bearing_x;
    float bearing_y;
    float advance;
};

class TextRenderable;
class Font {
public:
    Font(FT_Face face, int height);
    ~Font();

    Character *get_char(unsigned long c);

private:

    void load_char_from_font(unsigned long charcode);

    std::map<unsigned long, Character *> chars;
    FT_Face _face;
};