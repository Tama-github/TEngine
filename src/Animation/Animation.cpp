#include "Animation.h"

Animation::Animation ()
{}

Animation::~Animation () {

}

void Animation::addTranslation (const glm::vec3& translation) {
    _animations.push_back([=](glm::mat4 model)-> glm::mat4 {return glm::translate(model, translation);});
}

void Animation::addRotation (const float& angle, const glm::vec3& dirr) {
    _animations.push_back([=](glm::mat4 model)-> glm::mat4 {return glm::rotate(model, angle, dirr);});
}

void Animation::addScaling (const glm::vec3& scale) {
    _animations.push_back([=](glm::mat4 model)-> glm::mat4 {return glm::scale(model, scale);});
}

glm::mat4 Animation::playAnimation (const glm::mat4& model) {
    glm::mat4 res = model;

    for (unsigned int i = 0; i < _animations.size(); i++) {
        res = _animations[i](res);
    }
    return res;
}
