#ifndef LIGHT_H
#define LIGHT_H

#include "material.h"

class Light : public Material {
public:
    Light(glm::vec3 position, glm::vec3 color) :
        Material(position),
        _color(color) {}

    Light(glm::vec3 position) : Material(position) {_color = glm::vec3(0,0,0);}
    Light() : Material(glm::vec3(0,0,0)), _color(glm::vec3(0,0,0)) {}


private:
    glm::vec3 _color;

};

#endif
