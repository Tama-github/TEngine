#include "ssaoblurbuffer.h"
#include "../glassert.h"

SSAOBlurBuffer::SSAOBlurBuffer()
{
    RenderObject();
}

SSAOBlurBuffer::SSAOBlurBuffer(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
    RenderObject();

    _program = ShaderManager ("Shaders/SSAO/vertex_ssao.glsl", "Shaders/SSAO/fragment_ssao_blur.glsl");
    _program.genProgram();
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

void SSAOBlurBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SSAOBlurBuffer::setUniforms() {
    GL_CHECK_ERROR
    _program.use();
    GL_CHECK_ERROR
    std::string s = "ssaoInput";
    GL_CHECK_ERROR
    _program.setInt(s.c_str(), 0);
    GL_CHECK_ERROR
}

ShaderManager SSAOBlurBuffer::getProgram() {
    return _program;
}

unsigned int SSAOBlurBuffer::getSSAOColorBufferBlur() {
    return _ssaoColorBufferBlur;
}
