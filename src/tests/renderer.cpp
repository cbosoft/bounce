#include <gtest/gtest.h>
#include "../common/game/game.hpp"
#include "../common/renderer/renderer.hpp"

TEST(RendererTest, RendererInit) {
    auto &game = Game::ref();
    auto &rm = Renderer::get();
    EXPECT_TRUE(true);
}