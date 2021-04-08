#include <iostream>
#include "renderer.hpp"

Renderer::Renderer(int w, int h, const std::string &title)
{
    glewExperimental = GL_TRUE;
    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW.");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (!this->window)
        throw std::runtime_error("Failed to create window.");

    glfwMakeContextCurrent(this->window);
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Failed to init GLEW.");


    glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
    this->shaders["default"] = this->load_shader_program(
            "../resources/shaders/vertex/vertex.glsl", "../resources/shaders/fragment/fragment.glsl");
    this->shaders["background"] = this->load_shader_program(
            "../resources/shaders/vertex/notransform.glsl", "../resources/shaders/fragment/space.glsl");

    this->camera_size = arma::vec2{100, 100};

    this->varr = 0;
    glGenVertexArrays(1, &this->varr);
    glBindVertexArray(this->varr);

    static const GLfloat vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,
    };
    this->vbuf = 0;
    glGenBuffers(1, &this->vbuf);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_DYNAMIC_DRAW);
}