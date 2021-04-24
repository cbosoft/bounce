#include "renderer.hpp"

void Renderer::set_target_to_texture(GLuint id)
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
    glBindTexture(GL_TEXTURE_2D, id);

    int w = int(this->window_size[0] * this->_window_scale[0]);
    int h = int(this->window_size[1] * this->_window_scale[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);
}

void Renderer::set_target_to_screen()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}