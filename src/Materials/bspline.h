#ifndef BSPLINE_H
#define BSPLINE_H

#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>


#include <glm/glm.hpp>

class Bspline
{
public:
    Bspline(std::vector<glm::vec3> controlPts, int ordre, std::vector<int> nodalVec) : _controlPts(controlPts), _nodalVec(nodalVec), _ordre(ordre), _degre(ordre-1) {};
    Bspline(std::vector<glm::vec3> controlPts, int ordre)
        : _controlPts(controlPts), _ordre(ordre), _degre(ordre-1)
    {
        for (unsigned int i = 0; i < _ordre+_controlPts.size()+1; i++) {
            _nodalVec.push_back(i);
        }
    }
    glm::vec3 p(float u);
    int getOrdre();
    int getNbPoints();
    int getMin();
    int getMax();

private:
    std::vector<glm::vec3> _controlPts;
    std::vector<int> _nodalVec;
    int _ordre;
    int _degre;
};

#endif // BSPLINE_H
