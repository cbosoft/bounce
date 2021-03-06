#include <bounce/renderer/image/image.hpp>
#include <bounce/renderer/renderer.hpp>
#include <bounce/logging/logger.hpp>

/**
 * Initialise Renderer.
 *
 * Must be called once and before any rendering is attempted. Is called by Game#setup
 *
 * Give the renderer a ptr to the game, and set the desired window size (\p w, \p h) and window \p title. The function
 * performs important initialisation of the underlying renderer (OpenGL via glew and glfw).
 *
 * @param g Pointer to Game singleton
 * @param w Width of screen in pixels
 * @param h Height of screen in pixels
 * @param title Title of window
 */
void Renderer::init(Game *g, int w, int h, const std::string &title)
{
    this->game = g;
    this->window_size[0] = w;
    this->window_size[1] = h;

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

    this->error_check("renderer init");

    this->varr = 0;
    glGenVertexArrays(1, &this->varr);
    glBindVertexArray(this->varr);

    static const GLfloat vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,
    };
    glEnable(GL_MULTISAMPLE);
    this->vbuf = 0;
    glGenBuffers(1, &this->vbuf);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_DYNAMIC_DRAW);

    // alpha ftw
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // framebuffer
    glGenFramebuffers(1, &this->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

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
        Logger::ref() << LL_INFO << "Framebuffer init ok!\n";
    else
        Logger::ref() << LL_WARN << "Framebuffer init failed.\n"; // TODO should be error?

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

    glfwSwapInterval(0);

    // high dpi displays scale up contents; need to take that into account.
    // I don't think dpi is likely to change while the game is running; don't
    // need to update.
    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    this->_window_scale = {xscale, yscale};
    this->error_check("renderer init, end");

    this->time_last_render = _RDR_CLOCK_T::now();
}