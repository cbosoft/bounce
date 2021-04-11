#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLObject {
public:
    GLuint get_id() const { return this->id; }
    void set_id(GLuint id) { this->id = id; }

    virtual void use() const =0;
private:
    GLuint id =0;
};