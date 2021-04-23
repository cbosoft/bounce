#include "colour.hpp"

Colour::Colour(int r, int g, int b, int a)
{
    if (r > 255) r = 255;
    if (r < 0) r = 0;
    if (g > 255) g = 255;
    if (g < 0) g = 0;
    if (b > 255) b = 255;
    if (b < 0) b = 0;
    if (a > 255) a = 255;
    if (a < 0) a = 0;

    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}