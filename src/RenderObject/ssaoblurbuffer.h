#ifndef SSAOBLURBUFFER_H
#define SSAOBLURBUFFER_H

#include "renderobject.h"

class SSAOBlurBuffer : public RenderObject
{
public:
    SSAOBlurBuffer();
    void setUniforms();

private:
    unsigned int _ssaoColorBufferBlur;
};

#endif // SSAOBLURBUFFER_H
