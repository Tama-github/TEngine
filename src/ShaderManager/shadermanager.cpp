#include "shadermanager.h"

void ShaderManager::setVertexProgram(const char* vertex_filename) {
    _vertex_filename = vertex_filename;
}

void ShaderManager::setFragmentProgram(const char* fragment_filename) {
    _fragment_filename = fragment_filename;
}

void ShaderManager::genProgram() {
    GLint success;
    auto loader = ShaderLoader(_vertex_filename);
    _vertex_source = loader.load();
    loader.setFilename(_fragment_filename);
    _fragment_source = loader.load();

    // 1. Generate the shader
    _vertexshader = glCreateShader(GL_VERTEX_SHADER);
    // 2. set the source
    glShaderSource(_vertexshader, 1, &_vertex_source, NULL);
    // 3. Compile
    glCompileShader(_vertexshader);
    // 4. test for compile error
    glGetShaderiv(_vertexshader, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLint logSize = 0;
        glGetShaderiv(_vertexshader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> infoLog(logSize);
        glGetShaderInfoLog(_vertexshader, logSize, &logSize, &infoLog[0]);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << &infoLog[0] << std::endl;
    }

    // 1. Generate the shader
    _fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    // 2. set the source
    glShaderSource(_fragmentshader, 1, &_fragment_source, NULL);
    // 3. Compile
    glCompileShader(_fragmentshader);
    // 4. test for compile error
    glGetShaderiv(_fragmentshader, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLint logSize = 0;
        glGetShaderiv(_fragmentshader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> infoLog(logSize);
        glGetShaderInfoLog(_fragmentshader, logSize, &logSize, &infoLog[0]);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << &infoLog[0] << std::endl;
    }

    // 1. Generate the program
    _program = glCreateProgram();
    // 2. Attach the shaders to the program
    glAttachShader(_program, _vertexshader);
    glAttachShader(_program, _fragmentshader);
    // 3. Link the program
    glLinkProgram(_program);
    // 4. Test for link errors
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if(!success) {
        GLint logSize = 0;
        glGetShaderiv(_program, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> infoLog(logSize);
        glGetProgramInfoLog(_program, logSize, &logSize, &infoLog[0]);
        std::cerr << "ERROR::SHADER::LINK_FAILED\n" << &infoLog[0] << std::endl;
    }
    glDeleteShader(_vertexshader);
    glDeleteShader(_fragmentshader);
}

GLuint ShaderManager::getProgram() {
    return _program;
}


GLuint ShaderManager::getVertexshader() {
    return _vertexshader;
}

GLuint ShaderManager::getFragmentshader() {
    return _fragmentshader;
}

void ShaderManager::use() {
    glUseProgram(_program);
}

void ShaderManager::setInt(const char* name, GLint o) {
    glUniform1i(glGetUniformLocation(_program,name), o);
}






