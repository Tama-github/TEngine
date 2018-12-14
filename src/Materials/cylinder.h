#ifndef CYLINDER_H
#define CYLINDER_H

#include "material3DObject.h"

class Cylinder : public Material3DObject
{
public:
    Cylinder(glm::vec3 start, float length, unsigned int resolution, float radius);
};

#endif // CYLINDER_H
