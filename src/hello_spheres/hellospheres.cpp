#include "hellospheres.h"
#include <iostream>

#define deg2rad(x) float(M_PI)*(x)/180.f


SimpleSpheres::SimpleSpheres(int width, int height) :
    Scene(width, height),
    _camera(nullptr)
{
    init3DObjects();

    std::cout << "there are " << _nb3DObjects << " objects loaded." << std::endl;

    _vao = std::vector<GLuint>(_nb3DObjects);
    _vbo = std::vector<GLuint>(_nb3DObjects);
    _nbo = std::vector<GLuint>(_nb3DObjects);
    _ebo = std::vector<GLuint>(_nb3DObjects);


    // Initialize the geometry
    // 1. Generate geometry buffers
    for (unsigned int i = 0; i < _nb3DObjects; i++) {
        glGenBuffers(1, &_vbo[i]) ;
        glGenBuffers(1, &_nbo[i]) ;
        glGenBuffers(1, &_ebo[i]) ;
        glGenVertexArrays(1, &_vao[i]) ;
        // 2. Bind Vertex Array Object
        glBindVertexArray(_vao[i]);
            // 3. Copy our vertices array in a buffer for OpenGL to use
            glBindBuffer(GL_ARRAY_BUFFER, _vbo[i]);
            glBufferData(GL_ARRAY_BUFFER, _3DObjects[i].getVertices().size()*sizeof (GLfloat), _3DObjects[i].getVertices().data(), GL_STATIC_DRAW);
            // 4. Then set our vertex attributes pointers
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // 5. Copy our normals array in a buffer for OpenGL to use
            glBindBuffer(GL_ARRAY_BUFFER, _nbo[i]);
            glBufferData(GL_ARRAY_BUFFER, _3DObjects[i].getNormals().size()*sizeof (GLfloat), _3DObjects[i].getNormals().data(), GL_STATIC_DRAW);
            // 6. Copy our vertices array in a buffer for OpenGL to use
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            // 7. Copy our index array in a element buffer for OpenGL to use
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, _3DObjects[i].getIndices().size()*sizeof (GLfloat), _3DObjects[i].getIndices().data(), GL_STATIC_DRAW);
        //6. Unbind the VAO
        glBindVertexArray(0);
    }

    //add some lights sources
    GLfloat scale = 3.0;
    _lights.push_back(glm::vec3(scale,scale/3,scale/3));
    _lights.push_back(glm::vec3(-scale,scale/3,scale/3));
    _lights.push_back(glm::vec3(0,0,scale));

    //GLSL programs generation
    _activeshader = 0;
    _shaderselector.push_back(ShaderManager("Shaders/vertex_shader.glsl", "Shaders/fragment_light_shader.glsl"));
    _shaderselector.back().genProgram();
    _shaderselector.push_back(ShaderManager("Shaders/vertex_errors.glsl", "Shaders/fragment_errors_shader.glsl"));
    _shaderselector.back().genProgram();
    _shaderselector.push_back(ShaderManager("Shaders/vertex_phong_shader.glsl", "Shaders/fragment_phong_light_shader.glsl"));
    _shaderselector.back().genProgram();


    _camera.reset(new EulerCamera(glm::vec3(0.f, 0.f, 4.f)));
    _camera->setviewport(glm::vec4(0.f, 0.f, width, height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

SimpleSpheres::~SimpleSpheres() {

}

void SimpleSpheres::resize(int width, int height) {
    Scene::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}


void SimpleSpheres::draw() {
    Scene::draw();

    glUseProgram(_shaderselector[_activeshader].getProgram());

    GLint nbLightsLocation = glGetUniformLocation(_shaderselector[_activeshader].getProgram(), "nbLights");
    glProgramUniform1i(_shaderselector[_activeshader].getProgram(), nbLightsLocation, (GLint)_lights.size());

    GLint lightsLocation = glGetUniformLocation(_shaderselector[_activeshader].getProgram(), "lights");
    glProgramUniform3fv(_shaderselector[_activeshader].getProgram(), lightsLocation, _lights.size(),
                                  glm::value_ptr(_lights[0]));

    _view = _camera->viewmatrix();
    glUniformMatrix4fv( glGetUniformLocation(_shaderselector[_activeshader].getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(_shaderselector[_activeshader].getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

    GLint cameraPositionLocation = glGetUniformLocation(_shaderselector[_activeshader].getProgram(), "cameraPosition");
    glm::vec3 cp = _camera->position();
    glProgramUniform3f(_shaderselector[_activeshader].getProgram(), cameraPositionLocation, cp[0], cp[1], cp[2]);

    for (unsigned int i = 0; i < _nb3DObjects; i++) {
        //_3DObjects[i].playAnimation(); /* Play the animation of the 3D model*/

        glUniformMatrix4fv( glGetUniformLocation(_shaderselector[_activeshader].getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(_3DObjects[i]._model));

        glm::vec3 tmpColor = _3DObjects[i].getColor();
        GLint objectColorLocation = glGetUniformLocation(_shaderselector[_activeshader].getProgram(), "objectColor");
        glProgramUniform3f(_shaderselector[_activeshader].getProgram(), objectColorLocation,
                           (GLfloat) tmpColor[0], (GLfloat) tmpColor[1], (GLfloat) tmpColor[2]);

        glBindVertexArray(_vao[i]);
        glDrawElements(GL_TRIANGLES, _3DObjects[i].getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}

void SimpleSpheres::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void SimpleSpheres::mousemove(float xpos, float ypos) {
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void SimpleSpheres::keyboardmove(int key, double time) {
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool SimpleSpheres::keyboard(unsigned char k) {
    switch(k) {
        case ' ':
            _activeshader = (_activeshader + 1)% _shaderselector.size();
        default:
            return false;
    }
}

void SimpleSpheres::init3DObjects () {
    /* New objects to add */
    Sphere s1 = Sphere(glm::vec3(1.1,-1.1,0), glm::vec3(1,0.5,0.2));
    Sphere s2 = Sphere(glm::vec3(1.1,1.1,0), glm::vec3(0.2,0.2,0.6));
    Sphere s3 = Sphere(glm::vec3(-1.1,-1.1,0), glm::vec3(0.2,0.5,0.2));
    Sphere s4 = Sphere(glm::vec3(-1.1,1.1,0), glm::vec3(0.2,0.6,0.6));

    /* Init spheres */
    s1.initUVSphere(100,100);
    s2.initICOSphere(5);
    s3.initNormalizedCube(30);
    s4.initSpherifiedCube(30);

    /* Add animations to the added models */
//    s1.getAnimation().addRotation(0.01, glm::vec3(1,1,0));
//    s2.getAnimation().addRotation(0.01, glm::vec3(1,0,1));
//    s3.getAnimation().addRotation(0.01, glm::vec3(1,0,0));
    //s4.getAnimation().addRotation(0.01, glm::vec3(0,1,0));

    /* Add objects to the scene */
    _3DObjects.push_back(s1);
    _3DObjects.push_back(s2);
    _3DObjects.push_back(s3);
    _3DObjects.push_back(s4);

    _nb3DObjects = _3DObjects.size();
}
