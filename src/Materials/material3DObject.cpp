#include "material3DObject.h"

std::vector<GLfloat>& Material3DObject::getVertices() {
    return _vertices;
}

std::vector<GLfloat>& Material3DObject::getNormals() {
    return _normals;
}

std::vector<GLuint>& Material3DObject::getIndices() {
    return _indices;
}

glm::vec3 Material3DObject::getColor() {
    return _color;
}

void Material3DObject::updateShiftedVertices() {
    _model = glm::translate(_model, _position);
}

Animation& Material3DObject::getAnimation() {
    return _animation;
}

void Material3DObject::playAnimation() {
    _model = _animation.playAnimation(_model);
}
