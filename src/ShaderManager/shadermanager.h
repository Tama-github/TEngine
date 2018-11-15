#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <string>

#include "shaderloader.h"
#include "scene.h"
#include "../hello_camera/camera.h"

class ShaderManager {
public:
    ShaderManager(const char* vertex_filename, const char* fragment_filename) :
        _vertex_filename(vertex_filename),
        _fragment_filename(fragment_filename)
    {};

    ShaderManager()
    {};

    void setVertexProgram(const char* vertex_filename);
    void setFragmentProgram(const char* fragment_filename);
    void genProgram();
    GLuint getProgram();
    GLuint getVertexshader();
    GLuint getFragmentshader();
    void use();
    void setInt(const char* name, GLint o);
    void setFloat(const char* name, GLfloat o);
    void setVec3(const char* name, glm::vec3 v);

private:
    const char* _vertex_filename;
    const char* _fragment_filename;

    const char* _vertex_source;
    const char* _fragment_source;

    GLuint _program;
    GLuint _vertexshader;
    GLuint _fragmentshader;

};

#endif
