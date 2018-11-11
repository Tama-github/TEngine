#include "brdf.h"

std::string BRDF::getName() {
    return _name;
}

glm::vec3 BRDF::getAmbianteColor() {
    return _ambianteColor;
}

glm::vec3 BRDF::getDiffuseColor() {
    return _diffuseColor;
}

glm::vec3 BRDF::getSpecularColor() {
    return _specularColor;
}

glm::vec3 BRDF::getEmissiveColor() {
    return _emissiveColor;
}

float BRDF::getOpticDensity() {
    return _opticDensity;
}

int BRDF::getSpecularExp() {
    return _specularExp;
}

float BRDF::getTransparency() {
    return _transparency;
}

int BRDF::getLumParam() {
    return _lumParam;
}

void BRDF::setName(std::string name) {
    _name = name;
}

void BRDF::setAmbianteColor(glm::vec3 ac) {
    _ambianteColor = ac;
}

void BRDF::setDiffuseColor(glm::vec3 dc) {
    _diffuseColor = dc;
}

void BRDF::setSpecularColor(glm::vec3 sc) {
    _specularColor = sc;
}

void BRDF::setEmissiveColor(glm::vec3 ec) {
    _emissiveColor = ec;
}

void BRDF::setOpticDensity(float od) {
    _opticDensity = od;
}

void BRDF::setSpecularExp(int se) {
    _specularExp = se;
}

void BRDF::setTransparency(float t) {
    _transparency = t;
}

void BRDF::setLumParam(int lp) {
    _lumParam = lp;
}

