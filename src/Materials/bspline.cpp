#include "bspline.h"


glm::vec3 Bspline::p(float u) {
    int decalage = 0;
    while (u > _nodalVec[decalage+_ordre]) {
        decalage++;
    }

    std::vector<glm::vec3> pts;
    for (int i = 0; i < _ordre; i++){
        pts.push_back(_controlPts[decalage+i]);
    }

    for (int i = _ordre; i > 0; i--) {
        for (int j = 0; j < i-1; j++) {
            int u1 = decalage+1+j;
            int u2 = decalage+j+i;
            pts[j] = ((_nodalVec[u2]-u)/(_nodalVec[u2]-_nodalVec[u1]))*pts[j] + ((u-_nodalVec[u1])/(_nodalVec[u2]-_nodalVec[u1])) * pts[j+1];
        }
        decalage++;
    }
    return pts[0];
}

int Bspline::getOrdre() {
    return _ordre;
}

int Bspline::getNbPoints() {
    return _controlPts.size();
}

int Bspline::getMin() {
    return _nodalVec[_ordre-1];
}

int Bspline::getMax() {
    return _nodalVec[_controlPts.size()];
}
