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
#include "../transform/rect/rect.hpp"

/**
 * \brief Struct storing vertex information to be passed to OpenGL.
 *
 * Contains (x, y, z) information about the location of the corner in *world space*. Also contains colour information as
 * (r, g, b, a) floats (0-1). Finally, contains texture mapping information in (s, t).
 *
 * I do not know why I included z coords in a 2D game engine. I think I might remove it.
 *
 * \sa Colour
 */
struct Vertex {
    float x, y, z;
    float r, g, b, a;
    float s, t;
};

typedef std::chrono::system_clock _RDR_CLOCK_T;
typedef _RDR_CLOCK_T::time_point _RDR_TIME_PT_T;

class Game;
class Scene;

/**
 * \brief Singleton managing the rendering of stuff to screen.
 *
 * The Renderer gets a list of Renderable(s) from the current active scene (and those behind it if
 * Scene#is_insubstantial) and then calls Renderable#draw.
 *
 * \sa Renderer::render
 * \sa Renderer::render_scene
 * \sa Renderable::draw
 */
class Renderer {
public:
    /* Singleton: delete copy constructor and assignment op */
    Renderer(const Renderer &other) =delete;
    Renderer &operator=(const Renderer &other) =delete;

    /* dtor */
    ~Renderer();

    /* Get reference to singleton */
    static Renderer &get();

    /* Main method: render scene to screen */
    void render();

    /* target methods: change way the scene is draw. */
    void set_target_to_texture(GLuint target_id);
    void set_target_to_screen();

    /* Get window information. */
    GLFWwindow *get_window();
    const arma::vec2 &get_window_size() const;

    /* Define and set shaders. */
    void define_shader(const std::string &name, const std::string &vertex_name, const std::string &frag_name);
    void define_screen_effect_shader(const std::string &name, const std::string &vertex_name, const std::string &frag_name);
    void set_screen_effect(const std::string &name);
    void set_shader_variable(const std::string &shader, const std::string &variable, float v);
    void set_shader_variable(const std::string &shader, const std::string &variable, const arma::vec2 &v);
    void set_shader_variable(const std::string &shader, const std::string &variable, const arma::vec3 &v);
    void set_shader_variable(const std::string &shader, const std::string &variable, const arma::vec4 &v);

    /* Create and get textures. */
    void add_texture(const std::string &path);
    void add_texture(Texture *texture);
    Texture *get_texture(const std::string &name);

    /* Get GLObjects */
    GLuint get_shader(const std::string &name) const;
    GLuint get_vbuf() const;
    GLuint get_varr() const;

    /* Frame rate settings and value. */
    int get_fps() const;
    void set_max_fps(int max_fps);

    /* Convert between screen and world position. */
    arma::vec2 screen_pos_to_world_pos(const arma::vec2 &screen_pos) const;

    void set_window_name(const std::string &name) const;

private:
    Renderer();

    /* Initialise renderer: set initial screen size, and window title. Called in Game#setup */
    void init(Game *game, int w, int h, const std::string &title);

    void render_scene(const Scene *scene);
    bool should_render();

    /* Sanity checks. */
    void check_shaders() const;
    void error_check(const std::string &from) const;

    void update_common_shader_variables(const RectTransform *camera) const;

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

    friend class Game;
};
