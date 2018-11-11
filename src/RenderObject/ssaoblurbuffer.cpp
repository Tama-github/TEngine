#include "ssaoblurbuffer.h"

SSAOBlurBuffer::SSAOBlurBuffer()
{
    _program = ShaderManager ("Shaders/SSAO/vertex_ssao.glsl", "Shaders/SSAO/fragment_ssao_blur.glsl");
    // also create framebuffer to hold SSAO processing stage
    // -----------------------------------------------------
    glGenFramebuffers(1, &_fbo);
    //Blur stage
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glGenTextures(1, &_ssaoColorBufferBlur);
    glBindTexture(GL_TEXTURE_2D, _ssaoColorBufferBlur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ssaoColorBufferBlur, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAOBlurBuffer::setUniforms() {
    _program.use();
    _program.setInt("ssaoInput", 0);
}
