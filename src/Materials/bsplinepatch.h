#ifndef BSPLINEPATCH_H
#define BSPLINEPATCH_H

#include "bspline.h"
#include "material3DObject.h"

class BsplinePatch : public Material3DObject
{
public:
    BsplinePatch(glm::vec3 color, glm::vec3 position): Material3DObject(color, position) {};
    void addControlPoly (std::vector<glm::vec3> poly);
    void eval (int du, int dv);

private:
    glm::vec3 p(int u, int v);
    std::vector<std::vector<glm::vec3>> controlMesh;

};

#endif // BSPLINEPATCH_H
