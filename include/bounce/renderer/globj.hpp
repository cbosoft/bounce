#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * \brief Abstract class for an OpenGL object.
 *
 * OpenGL has a stateful design - and each object needs to be put into its relevant slot before it can be used for
 * anything. This class stores objects - their unique id - and provides a means to use it: GLObject#use.
 */
class GLObject {
public:

    /** @returns OpenGL object ID */
    [[nodiscard]] GLuint get_id() const { return this->_id; }

    /** Abstract method which tells OpenGL to use the object. This is overriden in the derived class where OpenGL
     * functions like glBindTexture are used to bind the texture to the GL state. */
    virtual void use() const =0;

protected:
    /** ID of the managed OpenGL object. This must be set in the derived class, probably in the constructor. */
    GLuint _id =0;
};