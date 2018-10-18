#include "bsplinepatch.h"


void BsplinePatch::addControlPoly (Bspline poly) {
    for (unsigned int i = 0; i < _controlMesh.size(); i++) {
        if (poly.getNbPoints() != _controlMesh[i].getNbPoints()
                || poly.getOrdre() != _ordre) {
            std::cerr << "Le nombre de points ou l'ordre de la Bspline d'entré ne conrespond pas à celles présentes dans le maillage de controlles." << std::endl;
            return;
        }
    }
    _controlMesh.push_back(poly);
}

int BsplinePatch::getMinU() {
    return _controlMesh[0].getMin();
}

int BsplinePatch::getMinV() {
    return _ordre;
}

int BsplinePatch::getMaxU() {
    return _controlMesh[0].getMax();
}

int BsplinePatch::getMaxV() {
    return _controlMesh.size();
}

void BsplinePatch::eval(float du, float dv) {
    _n = 0;
    _m = 0;
    int xc = 0;
    for (float u = getMinU(); u < getMaxU(); u+=du) {
        _n++;
        _m= 0;
        for (float v = getMinV(); v < getMaxV(); v+=dv) {
            glm::vec3 tmp = p(u,v);
            _vertices.push_back(tmp[0]);
            _vertices.push_back(tmp[1]);
            _vertices.push_back(tmp[2]);
            _m++;
        }
    }

    std::cout << "Compute triangles ..." << std::endl;
    makeTrianglesMesh();
    std::cout << "Compute normals ..." << std::endl;
    processNormals();
    updateShiftedVertices();
}

void BsplinePatch::makeTrianglesMesh() {
    for (int i = 0; i < _n-1; i++) {
        for (int j = 0; j < _m-1; j++) {
            _indices.push_back(i*_m+j);
            _indices.push_back((i+1)*_m+1+j);
            _indices.push_back(i*_m+1+j);

            _indices.push_back(i*_m+j);
            _indices.push_back((i+1)*_m+j);
            _indices.push_back((i+1)*_m+1+j);
        }
    }
}

void BsplinePatch::processNormals() {
    std::vector<glm::vec3> tmpNorm = std::vector<glm::vec3>(_n*_m, glm::vec3(0));
    for (uint32_t i = 0; i < _indices.size(); i+=3) {
        int ind = _indices[i]*3;
        glm::vec3 v1 = glm::vec3(_vertices[ind], _vertices[ind+1], _vertices[ind+2]);
        ind = _indices[i+1]*3;
        glm::vec3 v2 = glm::vec3(_vertices[ind], _vertices[ind+1], _vertices[ind+2]);
        ind = _indices[i+2]*3;
        glm::vec3 v3 = glm::vec3(_vertices[ind], _vertices[ind+1], _vertices[ind+2]);
        glm::vec3 tmp = glm::cross(v2-v1, v2-v3);
        tmpNorm[_indices[i]] += tmp;
        tmpNorm[_indices[i+1]] += tmp;
        tmpNorm[_indices[i+2]] += tmp;
    }

    for (uint32_t i = 0; i < tmpNorm.size(); i++)
         tmpNorm[i] = glm::normalize(tmpNorm[i]);

    for (uint32_t i = 0; i < tmpNorm.size(); i++) {
        _normals.push_back(tmpNorm[i][0]);
        _normals.push_back(tmpNorm[i][1]);
        _normals.push_back(tmpNorm[i][2]);
    }
}

glm::vec3 BsplinePatch::p(float u, float v) {
    std::vector<glm::vec3> tmp;
    for (unsigned int i = 0; i < _controlMesh.size(); i++) {
        tmp.push_back(_controlMesh[i].p(u));
    }
    Bspline tmpS = Bspline(tmp,_ordre);
    return tmpS.p(v);
}
