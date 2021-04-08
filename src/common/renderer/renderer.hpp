#pragma once
#include <string>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <armadillo>

#include "../physics/object/object.hpp"

class Renderer {
public:
    ~Renderer();
    static Renderer &get();
    static Renderer &init(int w, int h, const std::string &title);

    void add_object(PhysicsObject *object);
    void remove_object(PhysicsObject *object);
    void render();

    GLFWwindow *get_window();

private:
    Renderer(int w, int h, const std::string &title);

    void render(PhysicsObject *object);
    arma::vec2 world_pt_to_screen_pt(arma::vec2 pt);
    double world_len_to_screen_len(double l);

    void render_background();
    void draw_circle(const arma::vec2 &position, double radius);

    GLuint load_shader_program(const std::string &vertex_source, const std::string &fragment_source);
    GLuint compile_shader(const std::string &source, GLint shader_type);
    GLuint compile_vertex(const std::string &source);
    GLuint compile_fragment(const std::string &source);

    // camera position and size in world units
    Transform camera_transform;
    arma::vec2 camera_size;
    arma::vec2 window_size;

    GLFWwindow *window;
    std::map<std::string, GLuint> shaders;
    std::vector<PhysicsObject *> objects;
    unsigned int vbuf, varr;
};