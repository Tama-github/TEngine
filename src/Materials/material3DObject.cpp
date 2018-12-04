#include "material3DObject.h"

std::vector<GLfloat>& Material3DObject::getVertices() {
    return _vertices;
}

std::vector<GLfloat>& Material3DObject::getNormals() {
    return _normals;
}

std::vector<GLfloat>& Material3DObject::getTangentes() {
    return _tangentes;
}

std::vector<GLfloat>& Material3DObject::getBitangentes() {
    return _bitangentes;
}

std::vector<GLfloat>& Material3DObject::getTexCoords() {
    return _texCoords;
}

std::vector<GLuint>& Material3DObject::getIndices() {
    return _indices;
}

bool Material3DObject::getIsTextured() {
    return _isTextured;
}

void Material3DObject::setIsTextured(bool isTextured) {
    _isTextured = isTextured;
}

glm::vec3 Material3DObject::getColor() {
    return _color;
}

void Material3DObject::setColor(glm::vec3 color) {
    _color = color;
}

void Material3DObject::updateShiftedVertices() {
    _model = glm::translate(_model, _position);
}

void Material3DObject::changePosition(glm::vec3 moveTo) {
    _position = moveTo;
    updateShiftedVertices();
}

Animation& Material3DObject::getAnimation() {
    return _animation;
}

void Material3DObject::playAnimation() {
    _model = _animation.playAnimation(_model);
    std::cout << "ALO ? anim" << std::endl;
    for (unsigned int i = 0; i < _bonesWeight.size(); i++) {
        if (Bone * b = _skeleton->ith(i)) {
            std::cout << "Material3DObject::setupSkeleton current " << b->getIdx() << " :" << std::endl;
            glm::mat4 model =  b->getTransform();
            std::cout << model[0][0] << " " << model[0][1] << " " << model[0][2] << " " << model[0][3] << std::endl;
            std::cout << model[1][0] << " " << model[1][1] << " " << model[1][2] << " " << model[1][3] << std::endl;
            std::cout << model[2][0] << " " << model[2][1] << " " << model[2][2] << " " << model[2][3] << std::endl;
            std::cout << model[3][0] << " " << model[3][1] << " " << model[3][2] << " " << model[3][3] << std::endl;
            _skeleton->ith(i)->rotate(0.01,glm::vec3(1,1,0));
        } else {
            std::cout << "ha d'accord" << std::endl;
        }
    }
}

void Material3DObject::setupGL() {
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_nbo);
    glGenBuffers(1, &_tanbo);
    glGenBuffers(1, &_bitanbo);
    glGenBuffers(1, &_texcoordbo);

    glGenBuffers(1, &_ebo);

    glGenVertexArrays(1, &_vao);
    // 2. Bind Vertex Array Object
    glBindVertexArray(_vao);
        // 3. Copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof (GLfloat), _vertices.data(), GL_STATIC_DRAW);
        // 4. Then set our vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // 5. Copy our normals array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, _nbo);
        glBufferData(GL_ARRAY_BUFFER, _normals.size()*sizeof (GLfloat), _normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, _tanbo);
        glBufferData(GL_ARRAY_BUFFER, _tangentes.size()*sizeof (GLfloat), _tangentes.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, _bitanbo);
        glBufferData(GL_ARRAY_BUFFER, _bitangentes.size()*sizeof (GLfloat), _bitangentes.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ARRAY_BUFFER, _texcoordbo);
        glBufferData(GL_ARRAY_BUFFER, _texCoords.size()*sizeof (GLfloat), _texCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(4);


        // 7. Copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof (GLfloat), _indices.data(), GL_STATIC_DRAW);
    //6. Unbind the VAO
    glBindVertexArray(0);
}

void Material3DObject::draw(ShaderManager shader) {
    playAnimation();

    glm::vec3 tmpColor = _color;
    GLint objectColorLocation = glGetUniformLocation(shader.getProgram(), "objectColor");
    glProgramUniform3f(shader.getProgram(), objectColorLocation,
                       (GLfloat) tmpColor[0], (GLfloat) tmpColor[1], (GLfloat) tmpColor[2]);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glUseProgram(shader);

    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    for (unsigned int i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string num;
        std::string type = _textures[i]._type;

        if (type == "texture_diffuse")
            num = std::to_string(diffuseNr++);
        else if (type == "texture_specular")
            num = std::to_string(specularNr++);
        else if (type == "texture_normal")
            num = std::to_string(normalNr++);
        else if (type == "texture_height")
            num = std::to_string(heightNr++);

        glUniform1i(glGetUniformLocation(shader.getProgram(), (type+num).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]._id);
    }

    glUniform1i(glGetUniformLocation(shader.getProgram(), "isTextured"), _isTextured?1:0);
    glUniform3fv(glGetUniformLocation(shader.getProgram(), "material.diffuseColor"), 1, glm::value_ptr(_brdf.getDiffuseColor()));
    glUniform1f(glGetUniformLocation(shader.getProgram(), "material.transparency"), _brdf.getTransparency());
    glUniform3fv(glGetUniformLocation(shader.getProgram(), "material.specularColor"), 1, glm::value_ptr(_brdf.getSpecularColor()));

    glBindVertexArray(_vao);

    glUniformMatrix4fv( glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(_model));

    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    //glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, models.size());
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);

    //printMatrix(models[j]);

    /*for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << _model[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/

    //glBindVertexArray(_vao);
    //glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}

void Material3DObject::setupSkeleton (Bone* skeleton) {
    _skeleton = skeleton;
    unsigned int i = 0;
    Bone* current = _skeleton;
    /* Computing weight for each vertex */
    while (current != nullptr) {
        Bone* b = current;
        std::cout << "Material3DObject::setupSkeleton current " << b->getIdx() << " :" << std::endl;
        glm::mat4 model =  b->getTransform();
        std::cout << model[0][0] << " " << model[0][1] << " " << model[0][2] << " " << model[0][3] << std::endl;
        std::cout << model[1][0] << " " << model[1][1] << " " << model[1][2] << " " << model[1][3] << std::endl;
        std::cout << model[2][0] << " " << model[2][1] << " " << model[2][2] << " " << model[2][3] << std::endl;
        std::cout << model[3][0] << " " << model[3][1] << " " << model[3][2] << " " << model[3][3] << std::endl;
        _bonesWeight.emplace_back(current->wheightComputing(_vertices));
        i++;
        current = _skeleton->ith(i);
    }

    /* Nomalization of each weights */
    std::cout << "nb wheight per vertex : " << _bonesWeight.size() << std::endl;
    std::cout << "Starting normalization" << std::endl;

    for (i = 0; i < _vertices.size()/3; i++) {
        float norm = 0;
        std::cout << "i : " << i << std::endl;
        for (unsigned int j = 0; j < _bonesWeight.size(); j++) {
            //std::cout << "_bonesWeight[" << j << "][" << i << "] = " << _bonesWeight[j][i] << std::endl;
            norm += _bonesWeight[j][i] * _bonesWeight[j][i];
        }
        norm = sqrt(norm);
        //std::cout << "norm = " << norm << std::endl;
        if (norm != 0)
            for (unsigned int j = 0; j < _bonesWeight.size(); j++)
                _bonesWeight[j][i] /= norm;

    }
    std::cout << "nb wheight : " << _bonesWeight.size() << std::endl;
}

Bone* Material3DObject::getSkeleton() {
    return _skeleton;
}

void Material3DObject::updateVertices() {
    for (unsigned int i = 0; i < _vertices.size(); i+=3) {
        glm::vec3 p = glm::vec3(_vertices[i], _vertices[i+1], _vertices[i+2]);
        glm::vec4 res = glm::vec4(0.f,0.f,0.f,0.f);
        for (unsigned int j = 0; j < _bonesWeight.size(); j++) {
            Bone* btmp = _skeleton->ith(i);
            res += _bonesWeight[j][i/3] * btmp->getTransform() * btmp->getRestPositionInv() * glm::vec4(p,1);
        }
        _vertices[i] = res[0];
        _vertices[i+1] = res[1];
        _vertices[i+2] = res[2];
    }
}



