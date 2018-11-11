#ifndef GBUFFER_H
#define GBUFFER_H

#include "renderobject.h"

class GBuffer : public RenderObject
{
public:
    GBuffer();
    void bind();
    unsigned int getGPosition();
    unsigned int getGNormal();
    unsigned int getGAlbedo();
    ShaderManager getProgram();

private:
    /* textures */
    unsigned int _gPosition;
    unsigned int _gNormal;
    unsigned int _gAlbedo;


};

#endif // GBUFFER_H
