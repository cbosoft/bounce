#pragma once
#include <map>
#include <string>
#include <armadillo>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int texture_id;
    unsigned int w;
    unsigned int h;
    unsigned int bearing_x;
    unsigned int bearing_y;
    unsigned int advance;
};

class TextRenderable;
class Font {
public:
    Font(FT_Face face, int height);

    Character *get_char(char c);

private:
    std::map<char, Character *> chars;
};