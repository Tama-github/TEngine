#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "../opengl_stuff.h"
#include "../ShaderManager/shadermanager.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class RenderObject
{
public:
    RenderObject();
    void bind();
    void clear();

protected:
    ShaderManager _program;
    unsigned int _fbo;
    unsigned int _rbo;
};

#endif // RENDEROBJECT_H