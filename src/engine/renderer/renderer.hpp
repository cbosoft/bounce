#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <armadillo>

#include "texture/texture.hpp"
#include "../object/object.hpp"

struct Vertex {
    float x, y, z;
    float r, g, b, a;
    float s, t;
};

typedef std::chrono::system_clock _RDR_CLOCK_T;
typedef _RDR_CLOCK_T::time_point _RDR_TIME_PT_T;

class Game;
class Renderer {
public:
    Renderer(const Renderer &other) =delete;
    Renderer &operator=(const Renderer &other) =delete;
    ~Renderer();
    static Renderer &get();

    void init(Game *game, int w, int h, const std::string &title);
    void render();
    void set_target_to_texture(GLuint target_id);
    void set_target_to_screen();

    GLFWwindow *get_window();
    const arma::vec2 &get_window_size() const;

    void define_shader(const std::string &name, const std::string &vertex_name, const std::string &frag_name);
    void define_screen_effect_shader(const std::string &name, const std::string &vertex_name, const std::string &frag_name);
    void set_screen_effect(const std::string &name);

    void add_texture(const std::string &path);
    Texture *get_texture(const std::string &name);

    GLuint get_shader(const std::string &name) const;
    GLuint get_vbuf() const;
    GLuint get_varr() const;

    void check_shaders() const;
    void error_check(const std::string &from) const;

    int get_fps() const;
    void set_max_fps(int max_fps);

    arma::vec2 screen_pos_to_world_pos(const arma::vec2 &screen_pos) const;

private:
    Renderer();

    bool should_render();

    void update_shader_uniforms() const;

    GLuint get_screen_effect() const;

    GLuint load_shader_program(const std::string &vertex_name, const std::string &fragment_name);
    GLuint compile_shader(const std::string &name, GLint shader_type);
    GLuint compile_vertex(const std::string &name);
    GLuint compile_fragment(const std::string &name);

    static void window_size_callback(GLFWwindow *window, int width, int height);
    void set_window_size(int w, int h);
    void set_shader_filter_kernel(GLuint shader_id, float kernel_norm, const std::array<float, 9> &args);

    Game *game;
    arma::vec2 window_size, _window_scale;
    double aspect_ratio; // width over height

    GLFWwindow *window;
    std::string _screen_effect;
    std::map<std::string, GLuint> shaders, effects;
    std::map<std::string , Texture *> textures;
    unsigned int vbuf, varr;
    unsigned int fbo, txt, qbuf, qarr;

    int _max_fps, _min_mspf, _actual_fps;
    _RDR_TIME_PT_T time_last_render;
};
