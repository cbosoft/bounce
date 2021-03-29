// Appease the almighty linter
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <armadillo>
#include <gtest/gtest.h>

#include "../src/shapes/shapes.hpp"

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

#pragma clang diagnostic pop