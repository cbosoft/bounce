#include <bounce/renderer/renderer.hpp>
#include <bounce/logging/logger.hpp>

/**
 * Check for an OpenGL error. Does not raise exception, but logs the error.
 *
 * @param from String giving information about where the method was called, which is used to infer where the error ocurred.
 */
void Renderer::error_check(const std::string &from) const
{
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        // Process/log the error.
        std::string errtype = "unknown";
        switch (err) {
            case GL_INVALID_ENUM:
                errtype = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE:
                errtype = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:
                errtype = "GL_INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:
                errtype = "GL_STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:
                errtype = "GL_STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:
                errtype = "GL_OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errtype = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            case GL_CONTEXT_LOST:
                errtype = "GL_CONTEXT_LOST"; break;

            default:
                break;
        }
        Logger::ref() << LL_ERROR << "OpenGL error " << errtype << " found " << from << "\n";
        // TODO raise error?
    }
}