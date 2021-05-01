#pragma once

class Colour {
public:

    static Colour from_hsv(int h, int s, int v, int a=255) noexcept;
    static Colour from_hsv_f(double h, double s, double v, double a=1.0) noexcept;
    static Colour from_rgb(int r, int g, int b, int a=255) noexcept;
    static Colour from_rgb_f(double r, double g, double b, double a=1.0) noexcept;
    static Colour from_grayscale(int gy, int a=255) noexcept;
    static Colour from_grayscale_f(double gy, double a=1.0) noexcept;

    float rf() const;
    float gf() const;
    float bf() const;
    float af() const;

    int r, g, b, a;
private:
    Colour(int r, int g, int b, int a);
};

class Colours {
public:
    static const Colour red;
    static const Colour blue;
    static const Colour green;
    static const Colour yellow;
    static const Colour magenta;
    static const Colour cyan;

    static const Colour white;
    static const Colour light_gray;
    static const Colour gray;
    static const Colour dark_gray;
    static const Colour black;

    static const Colour clear;
};