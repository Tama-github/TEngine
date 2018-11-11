#ifndef SSAOBUFFER_H
#define SSAOBUFFER_H

#include "renderobject.h"

class SSAOBuffer : public RenderObject
{
public:
    SSAOBuffer();
    void setUniforms();
    ShaderManager getProgram();
    void renderQuad(unsigned int quadVAO);
    unsigned int getSSAOColorBuffer();

private:
    unsigned int _ssaoColorBuffer;

};

#endif // SSAOBUFFER_H
