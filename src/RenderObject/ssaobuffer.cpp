#include "ssaobuffer.h"
#include "../glassert.h"

SSAOBuffer::SSAOBuffer()
{
    RenderObject();
}

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

SSAOBuffer::SSAOBuffer(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
    RenderObject();
    GL_CHECK_ERROR
    _program = ShaderManager("Shaders/SSAO/vertex_ssao.glsl", "Shaders/SSAO/fragment_ssao.glsl");
    _program.genProgram();
    GL_CHECK_ERROR
    // also create framebuffer to hold SSAO processing stage
    // -----------------------------------------------------
    /*glGenFramebuffers(1, &_fbo);
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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

    /* glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
    // SSAO color buffer
    glGenTextures(1, &ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SSAO Framebuffer not complete!" << std::endl;*/
    glGenFramebuffers(1, &_fbo);
    GL_CHECK_ERROR
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
    GL_CHECK_ERROR

    glGenTextures(1, &_noiseTexture);
    GL_CHECK_ERROR
    //generateNoiseTexture();
    //kernel = generateKernel(64);

    std::vector<glm::vec3> ssaoNoise;
    std::uniform_real_distribution<GLfloat> randomFloats(0.f, 1.f);
    std::default_random_engine generator;

    for (unsigned int i=0; i < 16; i++) {
        glm::vec3 noise(randomFloats(generator) * 2.f - 1.f, randomFloats(generator) * 2.f - 1.f, 0.f);
        ssaoNoise.emplace_back(noise);
    }

    glBindTexture(GL_TEXTURE_2D, _noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    unsigned int nbSamples = 64;
    _kernel = std::vector<glm::vec3>();

    for (unsigned int i = 0; i < nbSamples; i++) {
        glm::vec3 sample(randomFloats(generator) * 2.f - 1.f, randomFloats(generator) * 2.f - 1.f, randomFloats(generator));
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);

        float scale = float(i) / nbSamples;

        scale = lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        _kernel.emplace_back(sample);
    }
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

std::vector<glm::vec3> SSAOBuffer::getKernel() {
    return _kernel;
}

unsigned int SSAOBuffer::getNoise() {
    return _noiseTexture;
}
