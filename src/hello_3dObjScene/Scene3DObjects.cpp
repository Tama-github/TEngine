#include "Scene3DObjects.h"
#include <iostream>

#define deg2rad(x) float(M_PI)*(x)/180.f


Scene3DObject::Scene3DObject(int width, int height) :
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
    GLfloat scale = 10.0;
    _lights.push_back(glm::vec3(scale,scale/2,0));
    _lights.push_back(glm::vec3(-scale,scale/2,0));
    _lights.push_back(glm::vec3(scale,scale,scale));
    //_lights.push_back(glm::vec3(0,0,0));

    //GLSL program generation
    _activeshader = 0;
    _shaderselector.push_back(ShaderManager("Shaders/vertex_shader.glsl", "Shaders/fragment_light_shader.glsl"));
    _shaderselector.back().genProgram();
    _shaderselector.push_back(ShaderManager("Shaders/vertex_phong_shader.glsl", "Shaders/fragment_phong_light_shader.glsl"));
    _shaderselector.back().genProgram();

    _camera.reset(new EulerCamera(glm::vec3(0.f, 0.f, 4.f)));
    _camera->setviewport(glm::vec4(0.f, 0.f, width, height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

Scene3DObject::~Scene3DObject() {

}

void Scene3DObject::resize(int width, int height) {
    Scene::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}


void Scene3DObject::draw() {
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
        _3DObjects[i].playAnimation();

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

void Scene3DObject::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void Scene3DObject::mousemove(float xpos, float ypos) {
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void Scene3DObject::keyboardmove(int key, double time) {
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool Scene3DObject::keyboard(unsigned char k) {

    switch(k) {
        case ' ':
            _activeshader = (_activeshader + 1)% _shaderselector.size();
        default:
            return false;
    }
}

void Scene3DObject::init3DObjects () {
    //ObjParser::parse(std::string("Models/cat.obj"), &_3DObjects, true);
    //ObjParser::parse(std::string("Models/suzanne.obj"), &_3DObjects, true);
    //ObjParser::parse(std::string("Models/armadillo.obj"), &_3DObjects, true);

    /* Add animations to the added models */
    //_3DObjects[0].getAnimation().addTranslation(glm::vec3(0.001,0,0));
    //_3DObjects[0].getAnimation().addTranslation(glm::vec3(0,0,-0.01));
    //_3DObjects[0].getAnimation().addRotation(0.01,glm::vec3(0,1,1));

    /*test sur les Bspline*/
    //Bspline test = Bspline (std::vector<glm::vec3>{glm::vec3(0,0,0), glm::vec3(1,1,0), glm::vec3(0,2,0), glm::vec3(2,3,0), glm::vec3(2,4,0), glm::vec3(1,5,0)},3);
    //std::cout << "polynome de controle : (0 0 0) / (1 1 0) / (0 2 0)" << std::endl << std::endl;
    //Bspline test = Bspline (std::vector<glm::vec3>{glm::vec3(-1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 0, 1), glm::vec3(2,1,1), glm::vec3(2, 2, 1)},3);
    /*glm::vec3 v;
    int xp = 0;
    int tf = (test.getMax()-test.getMin())/0.1;
    for (float i = test.getMin(); i < test.getMax(); i += 0.1) {
        v = test.p(i);
        std::cout << xp++ << "/" << tf << ": p(" << i << ") = (" << v[0] << " " << v[1] << " " << v[2] << ")" << std::endl;
        std::cout << "/////////////////////////////////////////////" << std::endl;
    }*/

    /*std::cout << "p(1.5)" << test.p(1.5) << std::endl;
    std::cout << "p(2)" << test.p(2.) << std::endl;
    std::cout << "p(2.5)" << test.p(2.5) << std::endl;
    std::cout << "p(3)" << test.p(3.) << std::endl;*/

    /*Test sur les patch Bspline*/
    BsplinePatch test = BsplinePatch (glm::vec3(-2,-4,-8),glm::vec3(0.1,0.4,0.8),3);

    for (int i = 0; i < 11; i ++ ) {
        Bspline b1 = Bspline (std::vector<glm::vec3>{glm::vec3(0,0,i), glm::vec3(1,1,i), glm::vec3(0,2,i), glm::vec3(2,3,i), glm::vec3(2,4,i), glm::vec3(1,5,i)},3);
        test.addControlPoly(b1);
    }

    test.eval(0.02,0.02);
    _3DObjects.push_back(test);

    _nb3DObjects = _3DObjects.size();
}
