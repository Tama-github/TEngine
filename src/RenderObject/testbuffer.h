#ifndef TESTBUFFER_H
#define TESTBUFFER_H

#include "renderobject.h"

class TestBuffer : public RenderObject
{
public:
    TestBuffer();
    void bind();
    void clear();
    void use(unsigned int quadVAO);

private:
    unsigned int _texColorBuffer;
};

#endif // TESTBUFFER_H
