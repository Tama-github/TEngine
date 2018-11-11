#include "ssaobuffer.h"

SSAOBuffer::SSAOBuffer()
{
    _program = ShaderManager("Shaders/SSAO/vertex_ssao.glsl", "Shaders/SSAO/fragment_ssao.glsl");
    // also create framebuffer to hold SSAO processing stage
    // -----------------------------------------------------
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    // SSAO color buffer
    glGenTextures(1, &_ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D, _ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ssaoColorBuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SSAO Framebuffer not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAOBuffer::setUniforms() {
    _program.use();
    _program.setInt("gPosition", 0);
    _program.setInt("gNormal", 1);
    _program.setInt("texNoise", 2);
}

void SSAOBuffer::renderQuad(unsigned int quadVAO) {
    glUseProgram(_program.getProgram());
    glBindVertexArray(quadVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, _ssaoColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

ShaderManager SSAOBuffer::getProgram() {
    return _program;
}
