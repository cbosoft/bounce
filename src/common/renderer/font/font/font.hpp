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

    Character *get_char(char c);

private:
    std::map<char, Character *> chars;
};