#include "ssaobuffer.h"

SSAOBuffer::SSAOBuffer()
{
    RenderObject();

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
    std::string p = "gPosition", n = "gNormal", t = "texNoise";
    _program.setInt(p.c_str(), 0);
    _program.setInt(n.c_str(), 1);
    _program.setInt(t.c_str(), 2);
}

void SSAOBuffer::renderQuad(unsigned int quadVAO) {
    glUseProgram(_program.getProgram());
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, _ssaoColorBuffer);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

unsigned int SSAOBuffer::getSSAOColorBuffer() {
    return _ssaoColorBuffer;
}

ShaderManager SSAOBuffer::getProgram() {
    return _program;
}
