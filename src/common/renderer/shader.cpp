#include <fstream>
#include <sstream>
#include "renderer.hpp"

GLuint Renderer::compile_shader(
        const std::string &source,
        GLint shader_type)
{
    GLuint shader_id = glCreateShader(shader_type);
    std::ifstream f(source);
    if (!f)
        throw std::runtime_error("Error reading shader source");

    std::stringstream ss;
    char c;
    while( (c = f.get()) != EOF) {
        ss << c;
    }

    std::string s = ss.str();
    char const *c_source = s.c_str();
    glShaderSource(shader_id, 1, &c_source, nullptr);
    glCompileShader(shader_id);

    int result = 0, loglen = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &loglen);
    if (loglen > 0) {
        std::vector<char> log(loglen+1);
        glGetShaderInfoLog(shader_id, loglen, nullptr, log.data());
        std::cerr
            << source << ": "
            << log.data() << std::endl;
        if (!result)
            return -1;
    }
    return shader_id;
}

GLuint Renderer::compile_vertex(const std::string &source)
{
    return this->compile_shader(source, GL_VERTEX_SHADER);
}

GLuint Renderer::compile_fragment(const std::string &source)
{
    return this->compile_shader(source, GL_FRAGMENT_SHADER);
}

GLuint Renderer::load_shader_program(
        const std::string &vertex_source,
        const std::string &fragment_source)
{
    std::cerr << "Loading shaders\n" << vertex_source << std::endl << fragment_source << std::endl;
    GLuint vertex_id = this->compile_vertex(vertex_source);
    GLuint fragment_id = this->compile_fragment(fragment_source);
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
    int result = 0, loglen = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &loglen);
    if (loglen > 0) {
        std::vector<char> log(loglen+1);
        glGetProgramInfoLog(program_id, loglen, nullptr, log.data());
        std::cerr << log.data() << std::endl;
        if (!result)
            return -1;
    }

    glDetachShader(program_id, vertex_id);
    glDetachShader(program_id, fragment_id);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    return program_id;
}