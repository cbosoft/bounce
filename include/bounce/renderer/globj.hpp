#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLObject {
public:
    GLuint get_id() const { return this->_id; }

    virtual void use() const =0;

protected:
    GLuint _id =0;
};