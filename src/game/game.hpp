#pragma once
#include <SDL2/SDL.h>
#include <armadillo>
#include <vector>
#include <chrono>

#include "../object/object.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::ratio<1, 1>> Duration;

class Game {
  public:
    Game(double dt=1e-4, double g=10, int w=1280, int h=960);
    ~Game();

    // Rendering
    void render_init();
    void render_step();
    void set_camera_size(double size);
    arma::vec2 world_pt_to_screen_pt(arma::vec2 );

    // Input
    void input_step();
    void keydown(SDL_Scancode scancode);

    // Physics
    void physics_init();
    void physics_step();
    void physics_timestep_objects();
    double check_time();

    // Logic
    void logic_step();

    // Loop
    void run();
    void quit();

  private:
    int w, h;
    double dt, g, irl_time, physics_time, time_scale;
    bool should_quit;
    SDL_Window *win;
    SDL_Renderer *renderer;

    // camera position and size in world units
    arma::vec2 camera_position;
    arma::vec2 camera_size;

    arma::vec2 window_size;
    double aspect_ratio;

    std::vector<PhysicsObject *> objects;

    Clock::time_point time_of_last_render, physics_epoch;
};
