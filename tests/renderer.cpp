#include <gtest/gtest.h>
#include <SDL2/SDL.h>

TEST(RendererTest, SDLInit) {
    EXPECT_FALSE(SDL_Init(SDL_INIT_EVERYTHING));
    SDL_Quit();
}