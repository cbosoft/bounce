#pragma once

class Colour {
public:

    static Colour from_hsv(int h, int s, int v) noexcept;
    static Colour from_hsv_f(double h, double s, double v) noexcept;
    static Colour from_rgb(int r, int g, int b) noexcept;
    static Colour from_rgb_f(double r, double g, double b) noexcept;
    static Colour from_grayscale(int gy) noexcept;
    static Colour from_grayscale_f(double gy) noexcept;

    float rf() const;
    float gf() const;
    float bf() const;

    int r, g, b;
private:
    Colour(int r, int g, int b);
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
};