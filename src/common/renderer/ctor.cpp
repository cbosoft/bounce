#include <iostream>
#include "image/image.hpp"
#include "renderer.hpp"

Renderer::Renderer(Game *game, int w, int h, const std::string &title)
: game(game)
, camera_angle(0.0)
, w(w)
, h(h)
, aspect_ratio(double(w)/double(h))
, fbo(0)
, txt(0)
, qbuf(0)
, qarr(0)
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
            "../resources/shaders/vertex/notransform.glsl", "../resources/shaders/fragment/alt_space.glsl");
    this->shaders["quad"] = this->load_shader_program(
            "../resources/shaders/vertex/quad.glsl", "../resources/shaders/fragment/ordered_dithering.glsl");
    this->shaders["sprite"] = this->load_shader_program(
            "../resources/shaders/vertex/vertex.glsl", "../resources/shaders/fragment/sprite.glsl");
    this->shaders["font"] = this->load_shader_program(
            "../resources/shaders/vertex/vertex.glsl", "../resources/shaders/fragment/font.glsl");

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

    glGenFramebuffers(1, &this->fbo);
    glBindTexture(GL_FRAMEBUFFER, this->fbo);

    glGenTextures(1, &this->txt);
    glBindTexture(GL_TEXTURE_2D, this->txt);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, this->txt, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "framebuffer ok!" << std::endl;

    glGenVertexArrays(1, &this->qarr);
    glBindVertexArray(this->qarr);
    glGenBuffers(1, &this->qbuf);
    glBindBuffer(GL_ARRAY_BUFFER, this->qbuf);
    static float quad_vertices[] = {
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices),
                 quad_vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->varr);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);

    stbi_set_flip_vertically_on_load(true);
}