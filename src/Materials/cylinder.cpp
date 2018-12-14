#include "cylinder.h"

Cylinder::Cylinder(glm::vec3 start, float length, unsigned int resolution, float radius) : Material3DObject() {
    _color = glm::vec3(0.7,0.2,0.3);
    _vertices = { start[0], start[1], start[2] };
    _indices = {};
    float pas = length/float(resolution);
    float sx = start[0];
    std::vector<GLfloat> circle = {
            sx, 0.f, 1.0f,
            sx, sqrt(2.f)/2.f, sqrt(2.f)/2.f,
            sx, 1.f, 0.0f,
            sx, sqrt(2.f)/2.f, -sqrt(2.f)/2.f,
            sx, 0.f, -1.f,
            sx, -sqrt(2.f)/2.f, -sqrt(2.f)/2.f,
            sx, -1.f, 0.0f,
            sx, -sqrt(2.f)/2.f, sqrt(2.f)/2.f
    };

    float tmp = 0;
    float i;
    for (i = sx; i <= sx+length; i+=pas) {
        for (unsigned int j = 0; j < circle.size(); j+=3) {
            _vertices.push_back(circle[j]+tmp);
            _vertices.push_back(circle[j+1]);
            _vertices.push_back(circle[j+2]);
        }
        tmp += pas;
    }

    _vertices.push_back(i);
    _vertices.push_back(0.f);
    _vertices.push_back(0.f);

    std::vector<GLuint> idx = {
        1,  9, 10,
        1, 10,  2,
        2, 10, 11,
        2, 11,  3,
        3, 11, 12,
        3, 12,  4,
        4, 12, 13,
        4, 13,  5,
        5, 13, 14,
        5, 14,  6,
        6, 14, 15,
        6, 15,  7,
        7, 15, 16,
        7, 16,  8,
        8,  9,  1,
        8, 16,  9
    };

    for (unsigned int i = 0; i < resolution-1; i++) {
        for (unsigned int j = 0; j < idx.size(); j++) {
            _indices.push_back(idx[j]+8*i);
        }
    }
}
