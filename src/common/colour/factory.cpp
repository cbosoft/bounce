#include "colour.hpp"
#include <cmath>

Colour Colour::from_rgb(int r, int g, int b) noexcept
{
    return {r, g, b};
}

Colour Colour::from_rgb_f(double r_f, double g_f, double b_f) noexcept
{
    int r = int(255.0*r_f);
    int g = int(255.0*g_f);
    int b = int(255.0*b_f);
    return {r, g, b};
}

Colour Colour::from_hsv(int h, int s, int v) noexcept
{
    double c = double(s*v)/255.0/255.0;
    double h60 = double(h)*60.0/255.0;
    double hmod2m1 = std::abs(std::fmod(h60, 2.0) - 1.0);
    double x = c * (1.0 - hmod2m1);
    double rprime, bprime, gprime;
    rprime = bprime = gprime = 0.0;
    switch (int(h60)) {
        case 0:
            rprime = c;
            gprime = x;
            break;
        case 1:
            rprime = x;
            gprime = c;
            break;
        case 2:
            bprime = c;
            gprime = x;
            break;
        case 3:
            bprime = x;
            gprime = c;
            break;
        case 4:
            rprime = x;
            gprime = c;
            break;
        default:
        case 5:
            rprime = c;
            gprime = x;
            break;
    }
    double m = double(v)/255.0 - c;
    int r = int((rprime + m)*255.0);
    int g = int((gprime + m)*255.0);
    int b = int((bprime + m)*255.0);

    return {r, g, b};
}

Colour Colour::from_hsv_f(double h, double s, double v) noexcept
{
    return Colour::from_hsv(int(h*255.0), int(s*255.0), int(v*255.0));
}

Colour Colour::from_grayscale(int gy) noexcept
{
    return {gy, gy, gy};
}

Colour Colour::from_grayscale_f(double gy) noexcept
{
    return Colour::from_grayscale(int(gy*255));
}