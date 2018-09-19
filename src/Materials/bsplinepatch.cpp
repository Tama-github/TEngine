#include "bsplinepatch.h"


void BsplinePatch::addControlPoly (std::vector<glm::vec3> poly) {
    controlMesh.add(poly);
}

void BsplinePatch::eval(int du, int dv) {

}

glm::vec3 BsplinePatch::p(int u, int v) {
    std::vector<glm::vec3> tmp;
    for (int i = 0; i < controlMesh.size) {

    }
}
