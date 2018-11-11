#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H


#include <glm/vec3.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>

#include <QGLFunctions>

#include "../Materials/composed3dobject.h"
#include "../Materials/material3DObject.h"
#include "../Texture/texture.h"
#include "../BRDF/brdf.h"

#include <assimp/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class ObjectLoader {

public:
    ObjectLoader(std::string path);
    bool objLoader(std::string name);
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec3> getTextures();
    std::vector<glm::vec3> getNormals();
    std::vector<int> getIndices();
    void setPath(std::string path);
    Composed3DObject getObj();
    void clear();
    const std::vector<BRDF> &getMaterials() const;

private:
    std::vector<Material3DObject> meshes;
    std::vector<BRDF> brdfs;
    std::vector<Texture> textures_loaded;
    std::vector<aiNode*> aiNodes;
    std::vector<aiNodeAnim*> aiNodesAnim;
    glm::mat4 globalTransformInv;
    //std::vector<Bone> bones;
    glm::mat4 cameraMatrix;
    GLuint texFormat;
    std::string path;
    std::string fileType;

    std::string getLineHeader(std::string line);
    std::string fillEmptyValues(std::string line);
    std::string remplaceSeparator(std::string line);
    std::vector<std::string> splitValues(std::string line);

    void processSubMesh(aiNode* subMesh, const aiScene *scene);
    Material3DObject processMesh(aiMesh *mesh, const aiScene *scene, const aiMatrix4x4 transformation);
    void processNodAnim(const aiScene *scene);
    std::string getExtension(std::string name);
    std::vector<Texture> loadMaterials(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory);
    void calcTangentBiTangent(aiMesh* mesh, std::vector<GLfloat>& tan, std::vector<GLfloat>& bitan);
    void standardScale(std::vector<GLfloat> &vertices);
    //void loadBones(unsigned int meshInd, aiMesh* mesh, std::vector<MeshObj::Bone>& bones);
    //Bone* findBone(std::string name);
    aiNode* findNode(std::string name);
    aiNodeAnim* findAiNodeAnim(std::string name);
    void processSubNode(aiNode* node);
    glm::mat4 toGlm(aiMatrix4x4 mat);
};


#endif // OBJECTLOADER_H
