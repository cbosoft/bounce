#include "font.hpp"

Character *Font::get_char(char c)
{
    return this->chars[c];
}