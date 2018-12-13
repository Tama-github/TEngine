#ifndef MATERIAL3DOBJECT_H
#define MATERIAL3DOBJECT_H

#include <vector>


#include "../opengl_stuff.h"
#include "material.h"
#include "../Animation/Animation.h"
#include "../Texture/texture.h"
#include "../ShaderManager/shadermanager.h"
#include "../BRDF/brdf.h"
#include "../Bone/bone.h"



class Material3DObject : public Material {
public:
    Material3DObject(glm::vec3 position, std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, std::vector<GLuint>& indices, glm::vec3 color = glm::vec3(0,0,0)) :
        Material(position),
        _vertices(vertices),
        _normals(normals),
        _indices(indices),
        _color(color),
        _model(glm::mat4(1.0)),
        _isTextured(false)
    {}

    Material3DObject(std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, std::vector<GLfloat> tangentes, std::vector<GLfloat> bitangentes, std::vector<GLfloat> texCoords, std::vector<GLuint>& indices, std::vector<Texture>& textures, BRDF& brdf) :
        Material(glm::vec3(0.f, 0.f, 0.f)),
        _vertices(vertices),
        _normals(normals),
        _tangentes(tangentes),
        _bitangentes(bitangentes),
        _texCoords(texCoords),
        _indices(indices),
        _textures(textures),
        _brdf(brdf),
        _color(glm::vec3(0.f,0.f,0.f)),
        _model(glm::mat4(1.0)),
        _isTextured(false)
    {}

    Material3DObject(glm::vec3 position, glm::vec3 color = glm::vec3(0,0,0)) :
        Material(position),
        _color(color),
        _model(glm::mat4(1.0)),
        _isTextured(false)
    {}

    std::vector<GLfloat>& getVertices();
    std::vector<GLfloat>& getNormals();
    std::vector<GLfloat>& getTexCoords();
    std::vector<GLfloat>& getTangentes();
    std::vector<GLfloat>& getBitangentes();
    std::vector<GLuint>& getIndices();

    bool getIsTextured();
    void setIsTextured(bool);

    glm::vec3 getColor();
    void setColor(glm::vec3 color);

    void changePosition(glm::vec3 moveTo);

    void setupGL();
    void draw(ShaderManager shader);

    //void setupSkeleton (Bone* skeleton);
    Bone* getSkeleton();

    /******** Depreciated *********/
    Animation& getAnimation();
    void updateShiftedVertices();
    void playAnimation();
    /******** *********** *********/

    //void moveBones ();

    //void updateVertices();


    glm::mat4 _model;
    std::vector<std::vector<GLfloat>> _bonesWeight;

protected:
    /* Gl handles */
    GLuint _vao;
    GLuint _vbo;
    GLuint _nbo;
    GLuint _tanbo;
    GLuint _bitanbo;
    GLuint _texcoordbo;

    GLuint _ebo;

    /* Vertices */
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _normals;
    std::vector<GLfloat> _tangentes;
    std::vector<GLfloat> _bitangentes;
    std::vector<GLfloat> _texCoords;
    std::vector<Texture> _textures;

    /* Triangles */
    std::vector<GLuint> _indices;

    /* Is this mesh have a texture ? */
    bool _isTextured;

    /* Object color things */
    glm::vec3 _color;
    BRDF _brdf;

    /* Animation things */
    Bone* _skeleton;
    Animation _animation;



};

#endif
