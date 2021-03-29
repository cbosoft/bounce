#include <armadillo>
#include <gtest/gtest.h>

#include "../src/shapes/shapes.hpp"

TEST(ShapeTest, Lines_Parallel) {
    Line line_a(0, 0, -1, 1), line_b(0, 1, -1, 1);

    arma::vec2 norm;
    bool v = line_a.intersects(line_b, norm);

    EXPECT_FALSE(v);
}