#include "renderobject.h"

RenderObject::RenderObject()
{

}

void RenderObject::bind () {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void RenderObject::clear () {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
}
