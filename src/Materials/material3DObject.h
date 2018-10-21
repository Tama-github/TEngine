#ifndef MATERIAL3DOBJECT_H
#define MATERIAL3DOBJECT_H

#include <vector>


#include "../opengl_stuff.h"
#include "material.h"
#include "../Animation/Animation.h"

class Material3DObject : public Material {
public:
    Material3DObject(glm::vec3 position, std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, std::vector<GLuint>& indices, glm::vec3 color = glm::vec3(0,0,0)) :
        Material(position),
        _vertices(vertices),
        _normals(normals),
        _indices(indices),
        _color(color)
    {/*glm::translate(_model,position);*/}

    Material3DObject(glm::vec3 position, glm::vec3 color = glm::vec3(0,0,0)) :
        Material(position),
        _color(color)
    {/*glm::translate(_model,position);*/}

    std::vector<GLfloat>& getVertices();
    std::vector<GLfloat>& getNormals();
    std::vector<GLuint>& getIndices();
    glm::vec3 getColor();
    /******** Depreciated *********/
    Animation& getAnimation();
    void updateShiftedVertices();
    void playAnimation();
    /******** *********** *********/

    glm::mat4 _model;

protected:
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _normals;
    std::vector<GLuint> _indices;

    std::vector<GLfloat> _shifted_vertices;

    glm::vec3 _color;

    Animation _animation;

};

#endif
