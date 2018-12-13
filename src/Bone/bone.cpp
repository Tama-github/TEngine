#include "bone.h"
/*
Note that the indexation is not stong enough yet
*/


Bone::Bone () : _parent(nullptr), _idx(0) {}
Bone::Bone (unsigned int idx) : _idx(idx) {}

/*void Bone::translate (glm::vec3 translate) {
    _transform = glm::translate(_transform*_restPosition, translate);
    if (_children) _children->setTransform(_children->getTransform()*_transform);
}

void Bone::rotate (float angle, glm::vec3 direction) {
    std::cout << "Bone" << _idx << "::matrix rotate :" << std::endl;
    std::cout << _transform[0][0] << " " << _transform[0][1] << " " << _transform[0][2] << " " << _transform[0][3] << std::endl;
    std::cout << _transform[1][0] << " " << _transform[1][1] << " " << _transform[1][2] << " " << _transform[1][3] << std::endl;
    std::cout << _transform[2][0] << " " << _transform[2][1] << " " << _transform[2][2] << " " << _transform[2][3] << std::endl;
    std::cout << _transform[3][0] << " " << _transform[3][1] << " " << _transform[3][2] << " " << _transform[3][3] << std::endl;
    _transform = glm::rotate(_transform, angle, direction);
    if (_children) _children->setTransform(_children->getTransform()*_transform);
}

void Bone::scale (glm::vec3 scale) {
    _transform = glm::scale(_transform*_restPosition, scale);
    if (_children) _children->setTransform(_children->getTransform()*_transform);
}*/

/*void Bone::setIdx(unsigned int idx) {
    _idx = idx;
}*/

/*void Bone::setChild (Bone* child) {
    _children = child;
}*/

/*Bone* Bone::ith (unsigned int idx) {
    if (_idx == idx) return this;
    for (const auto c : _children) {
        if(Bone* f = c->ith(idx))
            return f;
    }
    return nullptr;
}*/

/*unsigned int Bone::getIdx() {
    return _idx;
}

void Bone::setTransform(glm::mat4 t) {
    _transform = t;
}

glm::mat4 Bone::getTransform() {
    return _transform;
}

glm::vec3 Bone::getPosition() {
    return _position;
}*/

std::vector<GLfloat> Bone::wheightComputing(std::vector<GLfloat> vertices) {
    std::vector<GLfloat> res {};
    //std::cout << "Bone::wheightComputing : Bone " << _idx << "   _position = " << _position[0] << " " << _position[1] << " " << _position[2] << std::endl;
    for (unsigned int i = 0; i < vertices.size(); i+=3) {
        float R = _length/10.f;
        float R2 = R*R;
        float R8 = R*R*R*R*R*R*R*R;
        glm::vec3 pj = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]);
        glm::vec3 si = glm::vec3(-1.5f/2.f, 0.f, 0.f);
        res.push_back (1/R8 * (R2-glm::length(pj - si))*(R2-glm::length(pj - si))*(R2-glm::length(pj - si))*(R2-glm::length(pj - si)));
    }
    return res;
}

/*glm::mat4 Bone::getRestPositionInv() {
    return _restPositionInv;
}*/

/*Animation& Bone::getAnimation() {
    return _animation;
}

void Bone::playAnimation() {
    _transform = _animation.playAnimation(_transform);
}*/






