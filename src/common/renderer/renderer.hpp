#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <armadillo>

#include "texture/texture.hpp"
#include "../physics/object/object.hpp"

struct Vertex {
    float x, y, z;
    float r, g, b, a;
    float s, t;
};

class Game;
class Renderer {
public:
    Renderer(const Renderer &other) =delete;
    Renderer &operator=(const Renderer &other) =delete;
    ~Renderer();
    static Renderer &get();

    void init(Game *game, int w, int h, const std::string &title);
    void render();

    GLFWwindow *get_window();

    void define_shader(const std::string &name, const std::string &vertex_path, const std::string &frag_path);
    void define_screen_effect_shader(const std::string &name, const std::string &vertex_path, const std::string &frag_path);
    void set_screen_effect(const std::string &name);

    void set_camera_target(Transform *t);
    const Transform *get_camera_transform() const;
    void set_camera_width(double width);
    void set_camera_height(double height);
    void set_camera_diagonal(double diagonal);

    void add_texture(const std::string &path);
    Texture *get_texture(const std::string &name);

    GLuint get_shader(const std::string &name) const;
    GLuint get_vbuf() const;
    GLuint get_varr() const;

    void check_shaders() const;

private:
    Renderer();

    void update_shader_uniforms() const;

    GLuint get_screen_effect() const;

    GLuint load_shader_program(const std::string &vertex_source, const std::string &fragment_source);
    GLuint compile_shader(const std::string &source, GLint shader_type);
    GLuint compile_vertex(const std::string &source);
    GLuint compile_fragment(const std::string &source);

    void set_window_size(int w, int h);
    void set_shader_filter_kernel(GLuint shader_id, float kernel_norm, const std::array<float, 9> &args);

    Game *game;
    // camera position and size in world units
    Transform camera_transform;
    arma::vec2 camera_size;
    double camera_angle;
    int w, h;
    double aspect_ratio; // width over height

    GLFWwindow *window;
    std::string _screen_effect;
    std::map<std::string, GLuint> shaders, effects;
    std::map<std::string , Texture *> textures;
    unsigned int vbuf, varr;
    unsigned int fbo, txt, qbuf, qarr;
};
