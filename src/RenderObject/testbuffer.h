#ifndef TESTBUFFER_H
#define TESTBUFFER_H

#include "renderobject.h"

class TestBuffer : public RenderObject
{
public:
    TestBuffer();
    TestBuffer(unsigned int texColorBuffer);
    void setUniform(unsigned int i);
    void bind();
    void clear();
    void render();
    ShaderManager getProgram();
    unsigned int getTex();

private:
    unsigned int _quadVAO, _quadVBO;
    unsigned int _texColorBuffer;

    void initQuad();
};

#endif // TESTBUFFER_H
