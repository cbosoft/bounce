#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "../object/object.hpp"

class Game {
  public:
    Game(double dt=1e-3, double g=10, int w=640, int h=480);
    ~Game();

    // Rendering
    void render_init();
    void render_step();

    // Input
    void input_step();
    void keydown(SDL_Scancode scancode);

    // Physics
    void physics_step();

    // Loop
    void run();
    void quit();

  private:
    int w, h;
    double dt, g, time;
    bool should_quit;
    SDL_Window *win;
    SDL_Renderer *renderer;

    std::vector<PhysicsObject *> objects;
};
