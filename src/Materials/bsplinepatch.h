#ifndef BSPLINEPATCH_H
#define BSPLINEPATCH_H

#include "bspline.h"
#include "material3DObject.h"

class BsplinePatch : public Material3DObject
{
public:
    BsplinePatch(glm::vec3 color, glm::vec3 position, int ordre): _ordre{ordre}, _controlMesh{std::vector<Bspline>{}}, Material3DObject(color, position) {};
    void addControlPoly (Bspline poly);
    void eval (float du, float dv);


private:
    glm::vec3 p(int u, int v);
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
