#ifndef MATERIAL_H
#define MATERIAL_H

#include "../opengl_stuff.h"

class Material {
public:
    Material(glm::vec3 position) : _position(position) {}

protected:
    glm::vec3 _position;

};

#endif
