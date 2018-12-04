#include "composed3dobject.h"

void Composed3DObject::translate(glm::vec3 translate) {
    _model = glm::translate(_model, translate);
    for (unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i]._model = glm::translate(_meshes[i]._model, translate);
}

void Composed3DObject::rotate(float angle, glm::vec3 direction) {
    _model = glm::rotate(_model, angle, direction);
    for (unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i]._model = glm::rotate(_meshes[i]._model, angle, direction);
}

void Composed3DObject::scale(glm::vec3 scale) {
    _model = glm::scale(_model, scale);
    for (unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i]._model = glm::scale(_meshes[i]._model, scale);
}

void Composed3DObject::draw (ShaderManager shader) {
    for (unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i].draw(shader);
}

void Composed3DObject::addObject(Material3DObject obj) {
    _meshes.push_back(obj);
}

void Composed3DObject::setupGL() {
    for (unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i].setupGL();
}

std::vector<Material3DObject>& Composed3DObject::getMeshes() {
    return _meshes;
}

void Composed3DObject::setColor(glm::vec3 color) {
    for (unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i].setColor(color);
}
// TODO : Créer un objet dans la scène pour tester les os
