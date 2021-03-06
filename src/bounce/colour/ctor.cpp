#include <bounce/colour/colour.hpp>

/**
 * Construct a Colour from red, green, and blue components.
 *
 * @param r Red component as integer in range 0-255.
 * @param g Green component as integer in range 0-255.
 * @param b Blue component as integer in range 0-255.
 * @param a Alpha component as integer in range 0-255.
 */
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