#ifndef IMPORTED3DMODEL_H
#define IMPORTED3DMODEL_H

#include "material3DObject.h"

class Imported3DModel : public Material3DObject {
public:
    Imported3DModel(std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, std::vector<GLuint>& indices, glm::vec3 color) : Material3DObject(glm::vec3(0,0,0),vertices, normals, indices,color) {}
    Imported3DModel( glm::vec3 color) : Material3DObject(glm::vec3(0,0,0),color) {}

private:

};

#endif
