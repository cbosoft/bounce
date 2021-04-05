#pragma once
#include <SDL2/SDL.h>
#include <armadillo>
#include <vector>
#include <chrono>

#include "../transform/transform.hpp"
#include "../physics/engine/engine.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::ratio<1, 1>> Duration;

class Game {
  public:
    explicit Game(int w=1280, int h=960);
    ~Game();

    // Rendering
    void render_init();
    void render_step();
    void set_camera_size(double size);
    arma::vec2 world_pt_to_screen_pt(arma::vec2 pt);
    double world_len_to_screen_len(double l);

    // Input
    void input_step();
    void keydown(SDL_Scancode scancode);

    // Logic
    void logic_step();
    void add_object(PhysicsObject *obj);

    // Loop
    void run();
    void quit();

    Transform &get_camera();

  private:
    int w, h;
    bool should_quit;
    SDL_Window *win;
    SDL_Renderer *renderer;

    // camera position and size in world units
    Transform camera_transform;
    arma::vec2 camera_size;

    arma::vec2 window_size;
    double aspect_ratio;

    std::vector<PhysicsObject *> objects;

    Clock::time_point time_of_last_render, physics_epoch;
};
