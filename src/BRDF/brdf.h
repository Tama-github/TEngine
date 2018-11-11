#ifndef BRDF_H
#define BRDF_H

#include <vector>
#include <string>
#include <iostream>

#include <opengl_stuff.h>

class BRDF
{
public:
    BRDF() {};
    BRDF(std::string name) : _name(name) {};

    std::string getName();
    glm::vec3 getAmbianteColor();
    glm::vec3 getDiffuseColor();
    glm::vec3 getSpecularColor();
    glm::vec3 getEmissiveColor();
    float getOpticDensity();
    int getSpecularExp();
    float getTransparency();
    int getLumParam();

    void setName(std::string);
    void setAmbianteColor(glm::vec3);
    void setDiffuseColor(glm::vec3);
    void setSpecularColor(glm::vec3);
    void setEmissiveColor(glm::vec3);
    void setOpticDensity(float);
    void setSpecularExp(int);
    void setTransparency(float);
    void setLumParam(int);

protected:
    std::string _name;
    glm::vec3 _ambianteColor;
    glm::vec3 _diffuseColor;
    glm::vec3 _specularColor;
    glm::vec3 _emissiveColor;
    float _opticDensity;
    int _specularExp;
    float _transparency;
    int _lumParam;
};

#endif // BRDF_H
