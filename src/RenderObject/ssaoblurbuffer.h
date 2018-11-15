#ifndef SSAOBLURBUFFER_H
#define SSAOBLURBUFFER_H

#include "renderobject.h"

class SSAOBlurBuffer : public RenderObject
{
public:
    SSAOBlurBuffer();
    SSAOBlurBuffer(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void setUniforms();
    void bind();
    ShaderManager getProgram();
    unsigned int getSSAOColorBufferBlur();

private:
    unsigned int _ssaoColorBufferBlur;
};

#endif // SSAOBLURBUFFER_H
