#include <cmath>
#include <bounce/colour/colour.hpp>

/**
 * Construct a Colour from red, green, blue, and alpha components.
 *
 * @param r Red component as integer in range 0-255.
 * @param g Green component as integer in range 0-255.
 * @param b Blue component as integer in range 0-255.
 * @param a Alpha component as integer in range 0-255.
 * @return The constructed Colour.
 */
Colour Colour::from_rgb(int r, int g, int b, int a) noexcept
{
    return {r, g, b, a};
}

/**
 * Construct a Colour from red, green, blue, and alpha components.
 *
 * @param r Red component as float in range 0-1.
 * @param g Green component as float in range 0-1.
 * @param b Blue component as float in range 0-1.
 * @param a Alpha component as float in range 0-1.
 * @return The constructed Colour.
 */
Colour Colour::from_rgb_f(double r_f, double g_f, double b_f, double a_f) noexcept
{
    int r = int(255.0*r_f);
    int g = int(255.0*g_f);
    int b = int(255.0*b_f);
    int a = int(255.0*a_f);
    return {r, g, b, a};
}

/**
 * Construct a Colour from Hue Saturation Value (brightness), and alpha components.
 *
 * @param h Hue component as integer in range 0-255.
 * @param s Saturation component as integer in range 0-255.
 * @param v Value component as integer in range 0-255.
 * @param a Alpha component as integer in range 0-255.
 * @return The constructed Colour.
 */
Colour Colour::from_hsv(int h, int s, int v, int a) noexcept
{
    double c = double(s*v)/255.0/255.0;
    double hf = double(h)*360/255.;
    double hprime = hf/60.0;
    double hmod2m1 = std::abs(std::fmod(hprime, 2.0) - 1.0);
    double x = c * (1.0 - hmod2m1);
    double rprime, bprime, gprime;
    rprime = bprime = gprime = 0.0;
    switch (int(hprime)) {
        case 0:
            rprime = c;
            gprime = x;
            break;
        case 1:
            rprime = x;
            gprime = c;
            break;
        case 2:
            gprime = c;
            bprime = x;
            break;
        case 3:
            gprime = x;
            bprime = c;
            break;
        case 4:
            rprime = x;
            bprime = c;
            break;
        default:
        case 5:
            rprime = c;
            bprime = x;
            break;
    }
    double m = double(v)/255.0 - c;
    int r = int((rprime + m)*255.0);
    int g = int((gprime + m)*255.0);
    int b = int((bprime + m)*255.0);

    return {r, g, b, a};
}

/**
 * Construct a Colour from Hue Saturation Value (brightness), and alpha components.
 *
 * @param h Hue component as float in range 0-1.
 * @param s Saturation component as float in range 0-1.
 * @param v Value component as float in range 0-1.
 * @param a Alpha component as float in range 0-1.
 * @return The constructed Colour.
 */
Colour Colour::from_hsv_f(double h, double s, double v, double a) noexcept
{
    return Colour::from_hsv(int(h*255.0), int(s*255.0), int(v*255.0), int(a*255.0));
}

/**
 * Construct a Colour from shade and alpha component.
 *
 * @param gy Shade component as integer from 0-255.
 * @param a Alpha component as integer from 0-255.
 * @return The constructed Colour.
 */
Colour Colour::from_grayscale(int gy, int a) noexcept
{
    return {gy, gy, gy, a};
}

/**
 * Construct a Colour from shade and alpha component.
 *
 * @param gy Shade component as float 0-1.
 * @param a Alpha component as float 0-1.
 * @return The constructed Colour.
 */
Colour Colour::from_grayscale_f(double gy, double a) noexcept
{
    return Colour::from_grayscale(int(gy*255), int(a*255.0));
}