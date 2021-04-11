#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <armadillo>

#include "../physics/object/object.hpp"

class Game;
class Renderer {
public:
    ~Renderer();
    static Renderer &get();
    static Renderer &init(Game *game, int w, int h, const std::string &title);

    void render();

    GLFWwindow *get_window();

    void set_camera_target(Transform *t);
    const Transform *get_camera_transform() const;
    void set_camera_width(double width);
    void set_camera_height(double height);
    void set_camera_diagonal(double diagonal);

    GLuint get_shader(const std::string &name) const;
    GLuint get_vbuf() const;
    GLuint get_varr() const;

private:
    Renderer(Game *game, int w, int h, const std::string &title);

    void update_shader_uniforms() const;

    void render_background();

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
    std::map<std::string, GLuint> shaders;
    unsigned int vbuf, varr;
    unsigned int fbo, txt, qbuf, qarr;
};
