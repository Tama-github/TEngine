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
    glm::vec3 p(float u);


private:
    std::vector<glm::vec3> _controlPts;
    std::vector<int> _nodalVec;
    int _ordre;
    int _degre;
};

#endif // BSPLINE_H
