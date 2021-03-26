#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "object.hpp"

class Game {
  public:
    Game(double dt=1e-3, double g=10);
    ~Game();

    void render_step();
    void input_step();
    void physics_step();
    void keydown(SDL_Scancode scancode);
    void step();
    void run();
    void quit();

  private:
    double dt, g, time;
    bool should_quit;
    SDL_Window *win;
    SDL_Renderer *renderer;

    std::vector<PhysicsObject *> objects;
};
