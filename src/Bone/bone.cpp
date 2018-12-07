#include "bone.h"
/*
Note that the indexation is not stong enough yet
*/


Bone::Bone () : _parent(nullptr), _idx(0) {}
Bone::Bone (glm::vec3 position) :
    _restPosition(glm::inverse(glm::translate(glm::mat4(),position))),
    _parent(nullptr),
    _idx(0),
    _transform(glm::mat4()),
    _position(position)
{}

Bone::Bone (Bone* parent, glm::vec3 position) :
    _parent(parent),
    _restPositionInv(glm::inverse(glm::translate(glm::mat4(),position))),
    _restPosition(glm::translate(glm::mat4(),position)),
    _position(position),
    _transform(glm::mat4())
{
    _parent = parent;
    _parent->addChild(this);
}

void Bone::translate (glm::vec3 translate) {
    _transform = glm::translate(_transform*_restPosition, translate);
    for (unsigned int i = 0; i < _children.size(); i++) {
        _children[i]->setTransform(_children[i]->getTransform()*_transform);
    }
}

void Bone::rotate (float angle, glm::vec3 direction) {
    std::cout << "Bone" << _idx << "::matrix rotate :" << std::endl;
    std::cout << _transform[0][0] << " " << _transform[0][1] << " " << _transform[0][2] << " " << _transform[0][3] << std::endl;
    std::cout << _transform[1][0] << " " << _transform[1][1] << " " << _transform[1][2] << " " << _transform[1][3] << std::endl;
    std::cout << _transform[2][0] << " " << _transform[2][1] << " " << _transform[2][2] << " " << _transform[2][3] << std::endl;
    std::cout << _transform[3][0] << " " << _transform[3][1] << " " << _transform[3][2] << " " << _transform[3][3] << std::endl;
    _transform = glm::rotate(_transform, angle, direction);
    for (unsigned int i = 0; i < _children.size(); i++) {
        _children[i]->setTransform(_children[i]->getTransform()*_transform);
    }
}

void Bone::scale (glm::vec3 scale) {
    _transform = glm::scale(_transform*_restPosition, scale);
    for (unsigned int i = 0; i < _children.size(); i++) {
        _children[i]->setTransform(_children[i]->getTransform()*_transform);
    }
}

void Bone::setIdx(unsigned int idx) {
    _idx = idx;
}

void Bone::addChild (Bone* newChild) {
    unsigned int nbChildren = _children.size();
    _children.push_back(newChild);
    newChild->setIdx(_idx+nbChildren+1);
}

Bone* Bone::ith (unsigned int idx) {
    if (_idx == idx) return this;
    for (const auto c : _children) {
        if(Bone* f = c->ith(idx))
            return f;
    }
    return nullptr;
}

unsigned int Bone::getIdx() {
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
}

std::vector<GLfloat> Bone::wheightComputing(std::vector<GLfloat> vertices) {
    std::vector<GLfloat> res {};
    //std::cout << "Bone::wheightComputing : Bone " << _idx << "   _position = " << _position[0] << " " << _position[1] << " " << _position[2] << std::endl;
    for (unsigned int i = 0; i < vertices.size(); i+=3) {
        if (_parent) {
            glm::vec3 p = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]);
            float d = glm::dot(_position-_parent->getPosition() ,p-_parent->getPosition());
            std::cout << "d = " << d << std::endl;
            if (d < 0)
                res.push_back(0);
            else
                res.push_back(1);
        }
    }
    return res;
}

glm::mat4 Bone::getRestPositionInv() {
    return _restPositionInv;
}

/*Animation& Bone::getAnimation() {
    return _animation;
}

void Bone::playAnimation() {
    _transform = _animation.playAnimation(_transform);
}*/






