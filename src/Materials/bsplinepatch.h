#ifndef BSPLINEPATCH_H
#define BSPLINEPATCH_H

#include "bspline.h"
#include "material3DObject.h"

class BsplinePatch : public Material3DObject
{
public:
    BsplinePatch(glm::vec3 position, glm::vec3 color, int ordre): _ordre{ordre}, _controlMesh{std::vector<Bspline>{}}, Material3DObject(position, color) {};
    void addControlPoly (Bspline poly);
    void eval (float du, float dv);


private:
    glm::vec3 p(float u, float v);
    int getMinU();
    int getMinV();
    int getMaxU();
    int getMaxV();
    void makeTrianglesMesh();
    void processNormals();
    std::vector<Bspline> _controlMesh;
    int _ordre;
    int _n;
    int _m;

};

#endif // BSPLINEPATCH_H
