#pragma once
#include <cmath>
#include <array>

/**
 * Perlin noise generator.
 *
 * Adapted from the Java [reference implementation](https://mrl.cs.nyu.edu/~perlin/noise/).
 */
class Perlin {
public:
    Perlin() = default;

    static double noise3d(double x, double y, double z);

private:
    static double fade(double t);
    static double lerp(double t, double a, double b);
    static double grad(int hash, double x, double y, double z);

    static std::array<int, 512> p;
};