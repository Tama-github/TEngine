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
    return _controlMesh.size()+1;
}

void BsplinePatch::eval(float du, float dv) {
    _n = (getMaxU()-getMinU())/du;
    _m = (getMaxV()-getMinV())/dv;
    int nbVertex = (getMaxU()-getMinU())/du + (getMaxV()-getMinV())/dv;
    std::cout << "Compute mesh's vertexs ( nb vertex = "<< nbVertex <<") U(" << getMinU() << ", " << getMaxU() << ")  V(" << getMinV() << ", " << getMaxV() << ") ..." << std::endl;


    for (float u = getMinU(); u < getMaxU(); u+=du) {
        for (float v = getMinV(); v < getMaxV(); v+=dv) {
            glm::vec3 tmp = p(u,v);
            //std::cout << "Vertex number : " << u*v << std::endl;
            _vertices.push_back(tmp[0]);
            _vertices.push_back(tmp[1]);
            _vertices.push_back(tmp[2]);
        }
    }

    std::cout << "Compute triangles ..." << std::endl;
    makeTrianglesMesh();
    std::cout << "Compute normals ..." << std::endl;
    processNormals();
}

void BsplinePatch::makeTrianglesMesh() {
    for (int i = 0; i < _n-1; i++) {
        for (int j = 0; j < _m-1; j++) {
            _indices.push_back(i*_m+j);
            _indices.push_back((i+1)*_m+2+j);
            _indices.push_back((i+1)*_m+1+j);

            _indices.push_back(i*_m+j);
            _indices.push_back(i*_m+1+j);
            _indices.push_back((i+1)*_m+2+j);
        }
    }
}

void BsplinePatch::processNormals() {
    //std::cout << "Salut je cherche le problèlme :)" << std::endl;
    std::vector<glm::vec3> tmpNorm = std::vector<glm::vec3>(_vertices.size()/3, glm::vec3(0));
    //std::cout << "Ici c'est ok ?" << std::endl;
    for (uint32_t i = 0; i < _indices.size()/3; i+=3) {
        //std::cout << "Ici c'est un peu chiant" << std::endl;
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
        //std::cout << "On test la grosse boucle" << std::endl;
    }

    //std::cout << "La grosse boucle est passé !" << std::endl;
    for (uint32_t i = 0; i < tmpNorm.size(); i++)
         tmpNorm[i] = glm::normalize(tmpNorm[i]);

    //std::cout << "La normalisation c'est ok !" << std::endl;
    for (uint32_t i = 0; i < tmpNorm.size(); i++) {
        //std::cout << "Les petits derniers" << std::endl;
        _normals.push_back(tmpNorm[i][0]);
        _normals.push_back(tmpNorm[i][1]);
        _normals.push_back(tmpNorm[i][2]);
    }
    //std::cout << "TOUT EST OK :D" << std::endl;
}

glm::vec3 BsplinePatch::p(int u, int v) {
    std::vector<glm::vec3> tmp;
    for (unsigned int i = 0; i < _controlMesh.size(); i++) {
        tmp.push_back(_controlMesh[i].p(u));
    }
    Bspline tmpS = Bspline(tmp,_ordre);
    return tmpS.p(v);
}
