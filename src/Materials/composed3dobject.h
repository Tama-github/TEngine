#ifndef COMPOSED3DOBJECT_H
#define COMPOSED3DOBJECT_H

#include "../Materials/material3DObject.h"
#include "../ShaderManager/shadermanager.h"
#include "../opengl_stuff.h"

class Composed3DObject : public Material
{
public:
    Composed3DObject(glm::vec3 pos) :
        Material(pos),
        _model(glm::mat4())
    {};

    Composed3DObject(std::vector<Material3DObject> meshes) :
        Material(glm::vec3(0,0,0)),
        _model(glm::mat4()),
        _meshes(meshes)
    {};

    void translate(glm::vec3 translate);
    void rotate(float angle, glm::vec3 direction);
    void scale(glm::vec3 scale);
    void draw (ShaderManager shader);
    void addObject(Material3DObject obj);
    void setColor(glm::vec3 color);
    void setupGL();
    std::vector<Material3DObject>& getMeshes();

    glm::mat4 _model;


private:
    std::vector<Material3DObject> _meshes;


};

#endif // COMPOSED3DOBJECT_H
