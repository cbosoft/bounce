#pragma once

class Colour {
public:

    static Colour from_hsv(int h, int s, int v);
    static Colour from_hsv_f(double h, double s, double v);
    static Colour from_rgb(int r, int g, int b);
    static Colour from_rgb_f(double r, double g, double b);
    static Colour from_grayscale(int gy);
    static Colour from_grayscale_f(double gy);

    float rf() const;
    float gf() const;
    float bf() const;

    int r, g, b;
private:
    Colour(int r, int g, int b);
};