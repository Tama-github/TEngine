#include "bspline.h"


glm::vec3 Bspline::p(float u) {
    int decalage = 0;
    //std::cout << "_nodalVec[decalage+_ordre-1] = " << _nodalVec[decalage+_ordre-1] << std::endl;
    while (u > _nodalVec[decalage+_ordre]) {
        decalage++;
    }
    std::vector<glm::vec3> pts;
    for (int i = 0; i < _ordre; i++){
        pts.push_back(_controlPts[decalage+i]);
        std::cout << "pts in : " << pts[i][0] << " " << pts[i][1] << " " << pts[i][2] << std::endl;
    }

    int k = _ordre;
    for (int i = 0; i < _ordre -1; i++) {
        for (int j = 0; j < k-1; j++) {
            //std::cout << "decalage = " << decalage <<std::endl;
            //std::cout << "_nodalVec[decalage+1] = " << _nodalVec[decalage+1] << std::endl;
            //std::cout << "u = " << u << std::endl;
            //std::cout << "_nodalVec[decalage+1+k-1] = " << _nodalVec[decalage+1+k-1] << std::endl;
            //std::cout << "(_nodalVec[decalage+1+k-1]-u) = " << (_nodalVec[decalage+1+k-1]-u) << std::endl;
            //std::cout << "_nodalVec[decalage+1+k-1]-_nodalVec[decalage+1]) = " << _nodalVec[decalage+1+k-1]-_nodalVec[decalage+1] << std::endl;
            //std::cout << "((_nodalVec[decalage+1+k-1]-u)/(_nodalVec[decalage+1+k-1]-_nodalVec[decalage+1])) = " << ((_nodalVec[decalage+1+k-1]-u)/(_nodalVec[decalage+1+k-1]-_nodalVec[decalage+1])) << std::endl;
            //std::cout << "pts[j] = " << pts[j][0] << " " << pts[j][1] << " " << pts[j][2] << std::endl;
            //std::cout << "pts[j+1] = " << pts[j+1][0] << " " << pts[j+1][1] << " " << pts[j+1][2] << std::endl;
            //std::cout << "((u-_nodalVec[decalage+1])/(_nodalVec[decalage+1+k-1]-_nodalVec[decalage+1])) = " << ((u-_nodalVec[decalage+1])/(_nodalVec[decalage+1+k-1]-_nodalVec[decalage+1])) << std::endl;
            pts[j] = ((_nodalVec[decalage+1+k-1]-u)/(_nodalVec[decalage+1+k-1]-_nodalVec[decalage+1]))*pts[j] + ((u-_nodalVec[decalage+1])/(_nodalVec[decalage+1+k-1]-_nodalVec[decalage+1])) * pts[j+1];
        }
    }
    return pts[0];
}
