#include "bspline.h"


glm::vec3 Bspline::p(float u) {
    int decalage = 0;

    /*std::cout << "Nodal vec : " << std::endl;
    for (unsigned int i = 0; i < _nodalVec.size(); i++)
        std::cout << _nodalVec[i] << " ";
    std::cout << std::endl;*/
    //std::cout << "_nodalVec[decalage+_ordre-1] = " << _nodalVec[decalage+_ordre-1] << std::endl;
    while (u >= _nodalVec[decalage+_ordre]) {
        decalage++;
    }

    std::vector<glm::vec3> pts;
    for (int i = 0; i < _ordre; i++){
        pts.push_back(_controlPts[decalage+i]);
        std::cout << "pts in : " << pts[i][0] << " " << pts[i][1] << " " << pts[i][2] << "      ";
    }
    std::cout << std::endl;

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
            pts[j] = ((_nodalVec[decalage+k]-u)/(_nodalVec[decalage+k]-_nodalVec[decalage+1]))*pts[j] + ((u-_nodalVec[decalage+1])/(_nodalVec[decalage+k]-_nodalVec[decalage+1])) * pts[j+1];
        }
        //std::cout << "pts = " << pts[0][0] << " " << pts[0][1] << " " << pts[0][2] << std::endl;
        //std::cout << "______________________" << std::endl;
    }
    //std::cout << "res = " << pts[0][0] << " " << pts[0][1] << " " << pts[0][2] << std::endl;
    //std::cout << "////////////////////////////////" << std::endl;
    //std::cout << std::endl << std::endl;

    return pts[0];
}

int Bspline::getOrdre() {
    return _ordre;
}

int Bspline::getNbPoints() {
    return _controlPts.size();
}

int Bspline::getMin() {
    return _nodalVec[_ordre];
}

int Bspline::getMax() {
    return _nodalVec[_controlPts.size()];
}
