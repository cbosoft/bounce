#include <gtest/gtest.h>

#include <bounce/bounce.hpp>

TEST(RendererTest, RendererInit) {
    auto &game = Game::ref();
    auto &rm = Renderer::get();
    EXPECT_TRUE(true);
}