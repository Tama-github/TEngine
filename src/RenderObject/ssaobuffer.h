#ifndef SSAOBUFFER_H
#define SSAOBUFFER_H

#include "renderobject.h"

#include <random>

class SSAOBuffer : public RenderObject
{
public:
    SSAOBuffer();
    SSAOBuffer(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void setUniforms();
    ShaderManager getProgram();
    void renderQuad(unsigned int quadVAO);
    unsigned int getSSAOColorBuffer();
    std::vector<glm::vec3> getKernel();
    unsigned int getNoise();

private:
    unsigned int _ssaoColorBuffer;
    unsigned int _noiseTexture;
    std::vector<glm::vec3> _kernel;

};

#endif // SSAOBUFFER_H
