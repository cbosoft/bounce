#include <sstream>

#include <bounce/resources/manager.hpp>
#include <bounce/renderer/renderer.hpp>
#include <bounce/logging/logger.hpp>
#include <bounce/physics/engine/engine.hpp>

GLuint Renderer::compile_shader(const std::string &name, GLint shader_type)
{
    std::string source = ResourceManager::ref().get_path("shaders", name, ".glsl");
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
        Logger::ref() << source << ": " << log.data() << "\n";
        if (!result)
            return -1;
    }
    return shader_id;
}

GLuint Renderer::compile_vertex(const std::string &name)
{
    return this->compile_shader(name, GL_VERTEX_SHADER);
}

GLuint Renderer::compile_fragment(const std::string &name)
{
    return this->compile_shader(name, GL_FRAGMENT_SHADER);
}

GLuint Renderer::load_shader_program(const std::string &vertex_name, const std::string &fragment_name)
{
    Logger::ref() << LL_INFO << "Loading shaders \"" << vertex_name << "\" and \"" << fragment_name << "\"\n";
    GLuint vertex_id = this->compile_vertex(vertex_name);
    GLuint fragment_id = this->compile_fragment(fragment_name);
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
    int result = 0, loglen = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &loglen);
    if (loglen > 0 && !result) {
        std::vector<char> log(loglen+1);
        glGetProgramInfoLog(program_id, loglen, nullptr, log.data());
        Logger::ref() << LL_INFO << log.data();
        if (!result)
            return -1;
    }

    glDetachShader(program_id, vertex_id);
    glDetachShader(program_id, fragment_id);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    return program_id;
}

void Renderer::define_shader(const std::string &name, const std::string &vertex_name, const std::string &frag_name)
{
    GLuint shader = this->load_shader_program(vertex_name, frag_name);
    this->shaders[name] = shader;
}

void Renderer::define_screen_effect_shader(const std::string &name, const std::string &vertex_name, const std::string &frag_name)
{
    GLuint shader = this->load_shader_program(vertex_name, frag_name);
    this->effects[name] = shader;
}

GLuint Renderer::get_screen_effect() const
{
    auto it = this->effects.find(this->_screen_effect);
    if (it == this->effects.end()) {
        Logger::ref() << LL_WARN << "Cannot find effect shader \"" << this->_screen_effect << "\": falling back to default.\n";
        return this->effects.at("default");
    }
    return it->second;
}

void Renderer::set_screen_effect(const std::string &name)
{
    if (this->effects.find(name) != this->effects.end()) {
        this->_screen_effect = name;
    }
    else {
        Logger::ref() << LL_WARN << "Cannot find effect shader \"" << name << "\": not changing effect.\n";
    }
}

GLuint Renderer::get_shader(const std::string &name) const
{
    auto it = this->shaders.find(name);
    if (it != this->shaders.end()) {
        return it->second;
    }

    Logger::ref() << LL_WARN << "Cannot find shader \"" << name << "\": falling back to default.\n";
    return this->shaders.at(name);
}

void Renderer::check_shaders() const
{
    if (this->shaders.empty()) {
        throw std::runtime_error("Cannot render without shaders defined; must define at least a \"default\" shader.");
    }

    if (this->shaders.find("default") == this->shaders.end()) {
        throw std::runtime_error("Cannot find default shader.");
    }

    if (this->effects.empty()) {
        throw std::runtime_error("Cannot render without screen effect shaders defined; must define at least a \"default\" shader.");
    }

    if (this->effects.find("default") == this->effects.end()) {
        throw std::runtime_error("Cannot find default screen effect shader.");
    }
}

void Renderer::update_common_shader_variables(const RectTransform *camera) const
{
    arma::vec2 position = camera->get_position(), size = camera->get_size(), w = this->window_size;
    for (const auto &kv : this->shaders) {
        GLuint shader_id = kv.second;
        glUseProgram(shader_id);
        int loc = glGetUniformLocation(shader_id, "time");
        if (loc != -1) glUniform1f(loc, float(PhysicsEngine::ref().get_time()));

        loc = glGetUniformLocation(shader_id, "camera_position");
        auto cp = position;
        if (loc != -1) glUniform2f(loc, float(cp[0]), float(cp[1]));

        loc = glGetUniformLocation(shader_id, "camera_size");
        auto cs = size;
        if (loc != -1) glUniform2f(loc, float(cs[0]), float(cs[1]));

        loc = glGetUniformLocation(shader_id, "window_size");
        if (loc != -1) glUniform2f(loc, float(w[0]), float(w[1]));
    }
}

void Renderer::set_shader_filter_kernel(GLuint shader_id, float kernel_norm, const std::array<float, 9> &args)
{
    int loc = glGetUniformLocation(shader_id, "kernel_norm");
    if (loc != -1) glUniform1f(loc, kernel_norm);
    loc = glGetUniformLocation(shader_id, "kernel_a");
    if (loc != -1) glUniform3f(loc, args[0], args[1], args[2]);
    loc = glGetUniformLocation(shader_id, "kernel_b");
    if (loc != -1) glUniform3f(loc, args[3], args[4], args[5]);
    loc = glGetUniformLocation(shader_id, "kernel_c");
    if (loc != -1) glUniform3f(loc, args[6], args[7], args[8]);
}

void Renderer::set_shader_variable(const std::string &shader, const std::string &variable, float v)
{
    auto it = this->shaders.find(shader);
    if (it == this->shaders.end()) {
        it = this->effects.find(shader);
        if (it == this->effects.end()) {
            Logger::ref() << LL_WARN << "Could not find shader \"" << shader << "\"; unable to set variable \""
                          << variable << "\" value of " << v << "\n";
            return;
        }
    }

    GLuint shader_id = it->second;
    glUseProgram(shader_id);
    int loc = glGetUniformLocation(shader_id, variable.c_str());
    if (loc != -1) glUniform1f(loc, v);
    else
        Logger::ref() << LL_WARN << "Variable \"" << variable << "\" not found in shader \"" << shader
                      << "\"; could not set value of " << v << "\n";
}

void Renderer::set_shader_variable(const std::string &shader, const std::string &variable, const arma::vec2 &v)
{
    auto it = this->shaders.find(shader);
    if (it == this->shaders.end()) {
        it = this->effects.find(shader);
        if (it == this->effects.end()) {
            Logger::ref() << LL_WARN << "Could not find shader \"" << shader << "\"; unable to set variable \""
                          << variable << "\" value of " << v[0] << "," << v[1] << "\n";
            return;
        }
    }

    GLuint shader_id = it->second;
    glUseProgram(shader_id);
    int loc = glGetUniformLocation(shader_id, variable.c_str());
    if (loc != -1) glUniform2f(loc, float(v[0]), float(v[1]));
    else
        Logger::ref() << LL_WARN << "Variable \"" << variable << "\" not found in shader \"" << shader
                      << "\"; could not set value of " << v[0] << "," << v[1] << "\n";
}

void Renderer::set_shader_variable(const std::string &shader, const std::string &variable, const arma::vec3 &v)
{
    auto it = this->shaders.find(shader);
    if (it == this->shaders.end()) {
        it = this->effects.find(shader);
        if (it == this->effects.end()) {
            Logger::ref() << LL_WARN << "Could not find shader \"" << shader << "\"; unable to set variable \""
                          << variable << "\" value of " << v[0] << "," << v[1] << "," << v[2] << "\n";
            return;
        }
    }
    GLuint shader_id = it->second;
    glUseProgram(shader_id);
    int loc = glGetUniformLocation(shader_id, variable.c_str());
    if (loc != -1) glUniform3f(loc, float(v[0]), float(v[1]), float(v[2]));
    else
        Logger::ref() << LL_WARN << "Variable \"" << variable << "\" not found in shader \"" << shader
                      << "\"; could not set value of " << v[0] << "," << v[1] << "," << v[2] << "\n";

}

void Renderer::set_shader_variable(const std::string &shader, const std::string &variable, const arma::vec4 &v)
{
    auto it = this->shaders.find(shader);
    if (it == this->shaders.end()) {
        it = this->effects.find(shader);
        if (it == this->effects.end()) {
            Logger::ref() << LL_WARN << "Could not find shader \"" << shader << "\"; unable to set variable \""
                          << variable << "\" value of " << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "\n";
            return;
        }
    }

    GLuint shader_id = it->second;
    glUseProgram(shader_id);
    int loc = glGetUniformLocation(shader_id, variable.c_str());
    if (loc != -1) glUniform4f(loc, float(v[0]), float(v[1]), float(v[2]), float(v[3]));
    else
        Logger::ref() << LL_WARN << "Variable \"" << variable << "\" not found in shader \"" << shader
                      << "\"; could not set value of " << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "\n";
}
