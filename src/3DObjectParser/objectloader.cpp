#include "objectloader.h"

//
// Created by jb on 01/03/18.
//

#include <sstream>
#include <glm/geometric.hpp>
//#include "opengl_stuff.h"
#define STB_IMAGE_IMPLEMENTATION
#include "src/stb_image.h"
//#include <FreeImage.h>
//#include <FreeImage/Source/FreeImage.h>
#include "../glassert.h"

ObjectLoader::ObjectLoader(std::string path) {
    this->path = path;
    texFormat = GL_RGB;
    cameraMatrix = glm::mat4();
}

void ObjectLoader::setPath(std::string path) {
    this->path = path;
}

std::string ObjectLoader::getExtension(std::string name) {
    unsigned int index = 0;
    std::locale loc;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    //get last '.' index
    for (unsigned int i = 0; i < name.size(); i++) {
        if (name[i] == '.')
            index = i;
    }
    std::string extension = "";
    for (unsigned int i = index; i < name.size(); i++) {
        extension.append(sizeof(name[i]), name[i]);
    }
    return extension;
}

glm::mat4 ObjectLoader::toGlm(aiMatrix4x4 mat) {
    glm::mat4 transformGlm = glm::mat4(1);

    aiVector3t<ai_real> tScaling, tRotationAxis, tTranslation;
    ai_real tAngle;
    mat.Decompose(tScaling, tRotationAxis, tAngle, tTranslation);
    float angle = float(tAngle);
    glm::vec3 scaling, rotationAxis, translation;
    scaling = glm::vec3(tScaling[0], tScaling[1], tScaling[2]);
    rotationAxis = glm::vec3(tRotationAxis[0], tRotationAxis[1], tRotationAxis[2]);
    translation = glm::vec3(tTranslation[0], tTranslation[1], tTranslation[2]);

    transformGlm = glm::rotate(transformGlm, angle, rotationAxis);
    transformGlm = glm::translate(transformGlm, translation);
    transformGlm = glm::scale(transformGlm, scaling);

    /*
    transformGlm[0][0] = (GLfloat)mat.a1; transformGlm[0][1] = (GLfloat)mat.b1;
    transformGlm[0][2] = (GLfloat)mat.c1; transformGlm[0][3] = (GLfloat)mat.d1;
    transformGlm[1][0] = (GLfloat)mat.a2; transformGlm[1][1] = (GLfloat)mat.b2;
    transformGlm[1][2] = (GLfloat)mat.c2; transformGlm[1][3] = (GLfloat)mat.d2;
    transformGlm[2][0] = (GLfloat)mat.a3; transformGlm[2][1] = (GLfloat)mat.b3;
    transformGlm[2][2] = (GLfloat)mat.c3; transformGlm[2][3] = (GLfloat)mat.d3;
    transformGlm[3][0] = (GLfloat)mat.a4; transformGlm[3][1] = (GLfloat)mat.b4;
    transformGlm[3][2] = (GLfloat)mat.c4; transformGlm[3][3] = (GLfloat)mat.d4;
    */

    return transformGlm;
}



bool ObjectLoader::objLoader(std::string name) {
    std::string fileName = path + "/" + name;

    Assimp::Importer importer;

    /*aiProcess_Triangulate | aiProcess_JoinenticalVertices | aiProcess_FlipUVs | aiProcess_SortByPType | aiProcess_OptimizeMeshes;*/
    unsigned int flag = aiProcess_JoinIdenticalVertices | aiProcess_FlipWindingOrder | aiProcess_GenUVCoords | aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GlobalScale;
    const aiScene* scene = importer.ReadFile(fileName, flag);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error : " << importer.GetErrorString() << std::endl;
        return false;
    }

    fileType = getExtension(name);

    processSubNode(scene->mRootNode);
    //processNodAnim(scene);
    globalTransformInv = glm::inverse(toGlm(scene->mRootNode->mTransformation));

    processSubMesh(scene->mRootNode, scene);
    return true;
}

// TODO
void ObjectLoader::clear() {
    meshes.clear();
}

Composed3DObject ObjectLoader::getObj() {

    Composed3DObject obj = Composed3DObject(meshes);

    return obj;
}

aiMatrix4x4 turnColladaModel(aiMatrix4x4 mat) {

    aiMatrix4x4 base;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4;  j++)
            base[i][j] = 0;

    base[0][0] = 1;
    base[1][2] = 1;
    base[2][1] = 1;
    base[3][3] = 1;

    return base * mat;

}

aiMatrix4x4 turnObjModel(aiMatrix4x4 mat) {

    aiMatrix4x4 base;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4;  j++)
            base[i][j] = 0;

    base[0][0] = 1;
    base[1][1] = 1;
    base[2][2] = -1;
    base[3][3] = 1;

    return mat * base;
}



//debug function
void print_Matrix(glm::mat4 mat) {
    std::cout << "[ " <<
                 mat[0][0] << " "  << mat[0][1] << " " << mat[0][2] << " " << mat[0][3] << std::endl << "  " <<
                 mat[1][0] << " "  << mat[1][1] << " " << mat[1][2] << " " << mat[1][3] << std::endl << "  " <<
                 mat[2][0] << " "  << mat[2][1] << " " << mat[2][2] << " " << mat[2][3] << std::endl << "  " <<
                 mat[3][0] << " "  << mat[3][1] << " " << mat[3][2] << " " << mat[3][3] << " ]"
    << std::endl;
}


void ObjectLoader::processSubMesh(aiNode* subMesh, const aiScene *scene) {

    for (unsigned int i = 0; i < subMesh->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[subMesh->mMeshes[i]];
        aiMatrix4x4 transform = scene->mRootNode->mTransformation * subMesh->mTransformation;
        transform = turnObjModel(transform);
        if (fileType == ".dae") {
            transform = aiMatrix4x4() * subMesh->mTransformation;
            transform = turnColladaModel(transform);
        }

        Material3DObject obj = processMesh(mesh, scene, transform);
        //print_Matrix(toGlm(transform));
        //obj._model = toGlm(transform);
        meshes.emplace_back(obj);
    }

    aiNodes.emplace_back(subMesh);

    for (unsigned int i = 0; i < subMesh->mNumChildren; i++) {
        processSubMesh(subMesh->mChildren[i], scene);
    }

}

void ObjectLoader::processNodAnim(const aiScene* scene) {
    if (scene->mNumAnimations == 0)
        return;

    for (unsigned int i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
        aiNodesAnim.emplace_back(scene->mAnimations[0]->mChannels[i]);

}

void ObjectLoader::processSubNode(aiNode* node) {
    aiNodes.emplace_back(node);

    for (int i = 0; i < node->mNumChildren; i++)
        processSubNode(node->mChildren[i]);
}


void ObjectLoader::standardScale(std::vector<GLfloat> &vertices) {

    float max = -1;
    for (unsigned int i = 0; i < vertices.size(); i+=3) {
        if (max < vertices[i])
            max = vertices[i];
        if (max < vertices[i+1])
            max = vertices[i+1];
        if (max < vertices[i+2])
            max = vertices[i+2];
    }

    if (max > 1.f) {
        for (unsigned int i = 0; i < vertices.size(); i+=3) {
            vertices[i] /= max;
            vertices[i+1] /= max;
            vertices[i+2] /= max;
        }
    }
    else if (max < 1.f) {
        for (unsigned int i = 0; i < vertices.size(); i+=3) {
            vertices[i]   *= (1+max);
            vertices[i+1] *= (1+max);
            vertices[i+2] *= (1+max);
        }
    }
}


void ObjectLoader::calcTangentBiTangent(aiMesh* mesh, std::vector<GLfloat>& tan, std::vector<GLfloat>& bitan) {

    for (unsigned int i = 0; i < mesh->mNumVertices; i+=3) {

        glm::vec3 v0 = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        glm::vec3 v1 = glm::vec3(mesh->mVertices[i+1].x, mesh->mVertices[i+1].y, mesh->mVertices[i+1].z);
        glm::vec3 v2 = glm::vec3(mesh->mVertices[i+2].x, mesh->mVertices[i+2].y, mesh->mVertices[i+2].z);

        glm::vec2 uv0 = glm::vec2(mesh->mTextureCoords[i]->x, mesh->mTextureCoords[i]->y);
        glm::vec2 uv1 = glm::vec2(mesh->mTextureCoords[i+1]->x, mesh->mTextureCoords[i+1]->y);
        glm::vec2 uv2 = glm::vec2(mesh->mTextureCoords[i+2]->x, mesh->mTextureCoords[i+2]->y);

        glm::vec3 dpos1 = v1-v0;
        glm::vec3 dpos2 = v2-v0;

        glm::vec2 dUV1 = uv1-uv0;
        glm::vec2 dUV2 = uv2-uv0;

        float scalar = 1.f / (dUV1[0] * dUV2[1] - dUV1[1] * dUV2[0]);

        glm::vec3 tangent = scalar * (dpos1 * dUV2[1] - dpos2 * dUV1[1]);
        glm::vec3 bitangent = scalar * (dpos2 * dUV1[0] - dpos1 * dUV2[0]);

        for (int i = 0; i < 3; i++) {
            tan.push_back(tangent[0]);
            tan.push_back(tangent[1]);
            tan.push_back(tangent[2]);
            bitan.push_back(bitangent[0]);
            bitan.push_back(bitangent[1]);
            bitan.push_back(bitangent[2]);
        }
    }
}


Material3DObject ObjectLoader::processMesh(aiMesh *mesh, const aiScene *scene, const aiMatrix4x4 transformation) {

    //vertices process
    bool isTextured = false;
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> tangentes;
    std::vector<GLfloat> bitangentes;
    std::vector<GLfloat> texCoords;

    std::vector<GLfloat> tansTmp;
    std::vector<GLfloat> bitansTmp;
    if (!mesh->HasTangentsAndBitangents()) {
        if (mesh->HasTextureCoords(0)) {
            calcTangentBiTangent(mesh, tansTmp, bitansTmp);
        }
    }
    else
        isTextured = true;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 tmpVertex;
        glm::vec3 tmpNormal;
        glm::vec3 tmpTangente;
        glm::vec3 tmpBitangente;
        glm::vec2 tmpTexCoords;
        glm::vec3 temp;

        aiVector3D point = mesh->mVertices[i];
        point *= transformation;
        temp[0] = point.x;
        temp[1] = point.y;
        temp[2] = -point.z;
        tmpVertex = temp;

        temp[0] = mesh->mNormals[i].x;
        temp[1] = mesh->mNormals[i].y;
        temp[2] = mesh->mNormals[i].z;
        tmpNormal = temp;

        if (mesh->HasTangentsAndBitangents()) {
            temp[0] = mesh->mTangents[i].x;
            temp[1] = mesh->mTangents[i].y;
            temp[2] = mesh->mTangents[i].z;
            tmpTangente = temp;
            //std::cout << "tangente : " + std::to_string(i) << ", (" << temp[0] << ", " << temp[1] << ", " << temp[2] << ")" << std::endl;

            temp[0] = mesh->mBitangents[i].x;
            temp[1] = mesh->mBitangents[i].y;
            temp[2] = mesh->mBitangents[i].z;
            tmpBitangente = temp;

            tmpTangente = glm::normalize(tmpTangente - tmpNormal * glm::dot(tmpNormal, tmpTangente));

            tmpBitangente = glm::cross(tmpNormal, tmpTangente);

            if (glm::dot(glm::cross(tmpNormal, tmpTangente), tmpBitangente) < 0.0f) {
                tmpTangente = -tmpTangente;
            }
        }
        else {
            if (mesh->HasTextureCoords(0)) {
                tmpTangente[0] = tansTmp[(i*3)];
                tmpTangente[1] = tansTmp[(i*3)+1];
                tmpTangente[2] = tansTmp[(i*3)+2];
                tmpBitangente[0] = bitansTmp[(i*3)];
                tmpBitangente[1] = bitansTmp[(i*3)+1];
                tmpBitangente[2] = bitansTmp[(i*3)+2];
            }
        }

        if (mesh->mTextureCoords[0]) {
            glm::vec2 temp2;
            temp2[0] = mesh->mTextureCoords[0][i].x;
            temp2[1] = mesh->mTextureCoords[0][i].y;
            tmpTexCoords = temp2;
        } else {
            tmpTexCoords = glm::vec2(0.f, 0.f);
        }
        for (int j = 0; j < 3; j++) {
            vertices.push_back(tmpVertex[j]);
            normals.push_back(tmpNormal[j]);
            tangentes.push_back(tmpTangente[j]);
            bitangentes.push_back(tmpBitangente[j]);
        }
        texCoords.push_back(tmpTexCoords[0]);
        texCoords.push_back(tmpTexCoords[1]);
    }

    //indices process
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.emplace_back(face.mIndices[j]);
        }
    }


    //material process
    std::vector<Texture> textures;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterials(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterials(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        std::vector<Texture> normalMaps = loadMaterials(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        std::vector<Texture> heightMaps = loadMaterials(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    aiString name;
    BRDF brdf;
    if(AI_SUCCESS != scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_NAME, name))
        std::cerr << "Error : material has no name" << std::endl;
    else
        brdf = BRDF(std::string(name.C_Str()));

    aiColor3D color;
    if (AI_SUCCESS != scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
        std::cout << "pas de couleur diffuse" << std::endl;
        brdf.setDiffuseColor(glm::vec3(0));
    }
    else {
        brdf.setDiffuseColor(glm::vec3(color.r, color.g, color.b));
    }

    if (AI_SUCCESS != scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, color)) {
        std::cout << "pas de couleur speculaire" << std::endl;
        brdf.setSpecularColor(glm::vec3(0));
    }
    else {
        brdf.setSpecularColor(glm::vec3(color.r, color.g, color.b));
    }

    if (AI_SUCCESS != scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, color)) {
        //std::cout << "pas de couleur ambiante" << std::endl;
        brdf.setAmbianteColor(glm::vec3(0));
    }
    else {
        brdf.setAmbianteColor(glm::vec3(color.r, color.g, color.b));
    }

    if (AI_SUCCESS != scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_EMISSIVE, color)) {
        //std::cout << "pas de couleur emmissive" << std::endl;
        brdf.setEmissiveColor(glm::vec3(0));
    }
    else {
        brdf.setEmissiveColor(glm::vec3(color.r, color.g, color.b));
    }

    if (fileType == ".obj")
        standardScale(vertices);
    Material3DObject outObj = Material3DObject(vertices, normals, tangentes, bitangentes, texCoords, indices, textures, brdf);
    outObj.setIsTextured(isTextured);
    //outObj._model = glm::normalize(toGlm(transformation));

    return outObj;
}


unsigned int ObjectLoader::TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    std::cout << filename << std::endl;

    if (data)
    {
        GLuint format;
        switch (nrComponents) {
        case  1 :
            format = GL_RED;
            break;
        case 3 :
            format = GL_RGB;
            break;
        case 4 :
            format = GL_RGBA;
            break;
        default :
            format = GL_SRGB;
            break;
        }
        GL_CHECK_ERROR
        glBindTexture(GL_TEXTURE_2D, textureID);
        GL_CHECK_ERROR
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        GL_CHECK_ERROR
        glGenerateMipmap(GL_TEXTURE_2D);
        GL_CHECK_ERROR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        GL_CHECK_ERROR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        GL_CHECK_ERROR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        GL_CHECK_ERROR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        GL_CHECK_ERROR
        glBindTexture(GL_TEXTURE_2D, 0);
        GL_CHECK_ERROR


    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }

    stbi_image_free(data);

    return textureID;
}


std::vector<Texture> ObjectLoader::loadMaterials(aiMaterial *mat, aiTextureType type, std::string typeName) {

    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool exist = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j]._path.data(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                exist = true;
                break;
            }
        }
        if (!exist) {
            Texture texture;
            texture._id = TextureFromFile(str.C_Str(), path);
            texture._type = typeName;
            texture._path = std::string(str.C_Str());
            textures.push_back(texture);
            textures_loaded.emplace_back(texture);
        }
    }

    return textures;
}
/*
void FileLoader::loadBones(unsigned int meshInd, aiMesh* mesh, std::vector<MeshObj::Bone>& bones) {

    for (unsigned int i = 0; i < mesh->mNumBones; i++) {
        unsigned int boneId = 0;
        std::string name = std::string(mesh->mBones[i]->mName.C_Str());


        if (bones.find(name) == bones.end()) {
            boneId =
        }


    }

}*/

/*Bone* FileLoader::findBone(std::string name) {

    for (unsigned int i = 0; i < bones.size(); i++) {
        if (bones[i].getName() == name)
            return &bones.at(i);
    }

    return nullptr;
}*/

aiNode* ObjectLoader::findNode(std::string name) {
    for (unsigned int i = 0; i < aiNodes.size(); i++) {
        if (aiNodes[i]->mName.data == name )
            return aiNodes.at(i);
    }
    return nullptr;
}

/*aiNodeAnim* ObjectLoader::findAiNodeAnim(std::string name) {
    for (unsigned int i = 0; i < aiNodesAnim.size(); i++) {
        if (std::string(aiNodesAnim[i]->mNodeName.C_str()) == name)
            return aiNodesAnim[i];
    }
}*/





