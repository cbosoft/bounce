// Appease the almighty linter
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <iostream>
#include <armadillo>
#include <gtest/gtest.h>

#include "../common/shapes/shapes.hpp"

// Lines
TEST(ShapeTest, Lines_Parallel) {
    Line line_a(0, 0, -1, 1), line_b(0, 1, -1, 1);

    arma::vec2 norm;
    bool v = line_a.intersects(line_b, norm);

    EXPECT_FALSE(v);
}

TEST(ShapeTest, Lines_Parallel_Close) {
    Line line_a(0, 0, -1, 1), line_b(0, 1e-2, -1, 1);

    arma::vec2 norm;
    bool v = line_a.intersects(line_b, norm);

    EXPECT_FALSE(v);
}

TEST(ShapeTest, Lines_Parallel_VeryClose) {
    Line line_a(0, 0, -1, 1), line_b(0, 6e-3, -1, 1);

    arma::vec2 norm;
    bool v = line_a.intersects(line_b, norm);

    EXPECT_FALSE(v);
}

TEST(ShapeTest, Lines_Parallel_Touching) {
    Line line_a(0, 0, -1, 1), line_b(0, 4.5e-3, -1, 1);

    arma::vec2 norm;
    bool v = line_a.intersects(line_b, norm);

    EXPECT_TRUE(v);
}

TEST(ShapeTest, Lines_Intersecting_InRange) {
    Line line_a(-0.5, 0, -1, 1), line_b(0.5, 0, -1, 1);

    arma::vec2 norm;
    bool v = line_a.intersects(line_b, norm);

    EXPECT_TRUE(v);
}

TEST(ShapeTest, Lines_Intersecting_OutOfRange) {
    Line line_a(0.125, 1, -1, 1), line_b(0.5, 0, -1, 1);

    arma::vec2 norm;
    bool v = line_a.intersects(line_b, norm);

    EXPECT_FALSE(v);
}

// Circles
TEST(ShapeTest, Circle_Intersection) {
    HalfCircle c(1.0, true);
    Line l(0.0, 0.0, -1.5, 1.5);

    arma::vec2 norm;
    bool v = c.intersects(l, norm);

    EXPECT_TRUE(v);
}

TEST(ShapeTest, Circle_Intersection_OutOfRange) {
    HalfCircle c(1.0, true);
    Line l(0.0, -1e-2, -1.5, 1.5);

    arma::vec2 norm;
    bool v = c.intersects(l, norm);

    EXPECT_FALSE(v);
}

TEST(ShapeTest, Circle_Intersection_Overlapping) {
    HalfCircle upper(1.0, true), lower(1.0, false);
    arma::vec2 upper_pos{0, -0.5};
    upper.p = &upper_pos;

    arma::vec2 norm;
    bool v = upper.intersects(lower, norm);

    EXPECT_TRUE(v);
}

#pragma clang diagnostic pop