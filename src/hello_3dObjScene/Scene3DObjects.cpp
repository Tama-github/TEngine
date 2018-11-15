#include "Scene3DObjects.h"
#include <iostream>
#include "../glassert.h"

#define deg2rad(x) float(M_PI)*(x)/180.f


Scene3DObject::Scene3DObject(int width, int height) :
    Scene(width, height),
    _camera(nullptr)
    //_screenShader(ShaderManager("Shaders/vertex_fbo_test.glsl", "Shaders/fragment_fbo_test.glsl"))
{
    _rayon = 0.1;
    GL_CHECK_ERROR
    _gBuff = GBuffer(_width, _height);
    GL_CHECK_ERROR
    _ssaoBuff = SSAOBuffer(_width, _height);
    GL_CHECK_ERROR
    _ssaoBlurBuff = SSAOBlurBuffer(_width, _height);
    GL_CHECK_ERROR

    init3DObjects();
    GL_CHECK_ERROR
    initQuad();
    GL_CHECK_ERROR
    _geometryPass = ShaderManager("Shaders/SSAO/vertex_ssao_geometry.glsl", "Shaders/SSAO/fragment_ssao_geometry.glsl");
    _lightingPass = ShaderManager("Shaders/SSAO/vertex_ssao.glsl", "Shaders/SSAO/fragment_ssao_lighting.glsl");
    _geometryPass.genProgram();
    _lightingPass.genProgram();
    glGenTextures(1, &_noiseTexture);
    initSamples ();
    initNoise ();



    std::string p = "gPosition", n = "gNormal", a = "gAlbedo", s = "ssao", t = "texNoise", si = "ssaoInput";
    _lightingPass.use();
    _lightingPass.setInt(p.c_str() , 0);
    _lightingPass.setInt(n.c_str(), 1);
    _lightingPass.setInt(a.c_str(), 2);
    _lightingPass.setInt(s.c_str(), 3);

    _ssaoBuff.getProgram().use();
    _ssaoBuff.getProgram().setInt(p.c_str(), 0);
    _ssaoBuff.getProgram().setInt(n.c_str(), 1);
    _ssaoBuff.getProgram().setInt(t.c_str(), 2);

    _ssaoBlurBuff.getProgram().use();
    _ssaoBlurBuff.getProgram().setInt(si.c_str(), 0);

    GL_CHECK_ERROR
    //_tbuff = TestBuffer(_gBuff.getGAlbedo());
    //_tbuff.setUniform(0);

    std::cout << "there are " << _nb3DObjects << " objects loaded." << std::endl;

    //add some lights sources
    GL_CHECK_ERROR
    GLfloat scale = 10.0;
    _lights.push_back(glm::vec3(scale,scale/2,0));
    _lights.push_back(glm::vec3(-scale,scale/2,0));
    _lights.push_back(glm::vec3(scale,scale,scale));
    //_lights.push_back(glm::vec3(0,0,0));

    //GLSL program generation
    GL_CHECK_ERROR
    _activeshader = 0;
    _shaderselector.push_back(ShaderManager("Shaders/vertex_shader.glsl", "Shaders/fragment_light_shader.glsl"));
    _shaderselector.back().genProgram();
    _shaderselector.push_back(ShaderManager("Shaders/vertex_phong_shader.glsl", "Shaders/fragment_phong_light_shader.glsl"));
    _shaderselector.back().genProgram();
    _shaderselector.push_back(ShaderManager("Shaders/vertex_phong_shader_new.glsl", "Shaders/fragment_phong_light_shader_new.glsl"));
    _shaderselector.back().genProgram();
    GL_CHECK_ERROR
    //_screenShader.genProgram();


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
    //GLint qt_buffer;
    //glGetIntegerv(GL_FRAMEBUFFER_BINDING, &qt_buffer);
    //std::cout << qt_buffer << std::endl;
    Scene::draw();
    //drawScene();
    //drawFrameBuffer();
    drawSSAO();
}

void Scene3DObject::drawScene() {
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
        _3DObjects[i].draw(_shaderselector[_activeshader]);
    }
}

void Scene3DObject::drawFrameBuffer() {
    // first pass
    /*glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
    glEnable(GL_DEPTH_TEST);*/
    _tbuff.bind();
    drawScene();

    // second pass
    /*glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);*/

    /*glUseProgram(_screenShader.getProgram());
    glBindVertexArray(quadVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, _texColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);*/
    _tbuff.render();
}

void Scene3DObject::drawSSAO() {
    //initSamples ();
    //initNoise ();
    GLint currentFB;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFB);
    _view = _camera->viewmatrix();
    //std::cout << "begin SSAO draw" << std::endl;
    /* Geometry Pass */
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    _gBuff.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*std::cout << "View : " << std::endl;
    std::cout << _view[0][0] << " " << _view[0][1] << " " << _view[0][2] << " " << _view[0][3] << std::endl;
    std::cout << _view[1][0] << " " << _view[1][1] << " " << _view[1][2] << " " << _view[1][3] << std::endl;
    std::cout << _view[2][0] << " " << _view[2][1] << " " << _view[2][2] << " " << _view[2][3] << std::endl;
    std::cout << _view[3][0] << " " << _view[3][1] << " " << _view[3][2] << " " << _view[3][3] << std::endl;
    std::cout << std::endl;*/
    /* config gBuffer */
    //std::cout << "Config Gbuffer" << std::endl;
    _geometryPass.use();


    glUniformMatrix4fv( glGetUniformLocation(_geometryPass.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(_geometryPass.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

    /* draw objects */
    //std::cout << "Draw objects" << std::endl;
    for (unsigned int i = 0; i < _nb3DObjects; i++) {
        _3DObjects[i].draw(_geometryPass);
    }

    /* gPosition display */
    /*glBindFramebuffer(GL_FRAMEBUFFER, currentFB); // back to default
    _tbuff.getProgram().use();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _gBuff.getGPosition());	// use the color attachment texture as the texture of the quad plane
    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);*/

    /* SSAO Pass */
    //std::cout << "SSAO" << std::endl;
    _ssaoBuff.bind();
    glClear(GL_COLOR_BUFFER_BIT);

    _ssaoBuff.getProgram().use();

    _ssaoBuff.getProgram().setInt("width", _width);
    _ssaoBuff.getProgram().setInt("height", _height);
    _ssaoBuff.getProgram().setFloat("radius", _rayon);
    GL_CHECK_ERROR
    for (unsigned int i = 0; i < _ssaoKernel.size(); ++i) {
        GL_CHECK_ERROR
        std::string n = "samples[" + std::to_string(i) + "]";
        _ssaoBuff.getProgram().setVec3(n.c_str(), _ssaoKernel[i]);
    }
    GL_CHECK_ERROR
    //std::cout << "Config tex" << std::endl;
    glUniformMatrix4fv( glGetUniformLocation(_ssaoBuff.getProgram().getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _gBuff.getGPosition());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _gBuff.getGNormal());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _noiseTexture);
    GL_CHECK_ERROR

    renderQuad();

    GL_CHECK_ERROR
    glBindFramebuffer(GL_FRAMEBUFFER, currentFB); // back to default
    _tbuff.getProgram().use();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ssaoBuff.getSSAOColorBuffer());	// use the color attachment texture as the texture of the quad plane
    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    GL_CHECK_ERROR

    /* SSAO Blur Pass */
    /*glBindFramebuffer(GL_FRAMEBUFFER, currentFB);

    _ssaoBlurBuff.bind();
    _ssaoBlurBuff.getProgram().use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ssaoBuff.getSSAOColorBuffer());

    renderQuad();*/


    /*glBindFramebuffer(GL_FRAMEBUFFER, currentFB); // back to default
    _tbuff.getProgram().use();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ssaoBlurBuff.getSSAOColorBufferBlur());	// use the color attachment texture as the texture of the quad plane
    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);*/


    /* Lighting Pass */

    /*glBindFramebuffer(GL_FRAMEBUFFER, currentFB);

    _lightingPass.use();
    glUseProgram(_lightingPass.getProgram());

    GLint nbLightsLocation = glGetUniformLocation(_lightingPass.getProgram(), "nbLights");
    glProgramUniform1i(_lightingPass.getProgram(), nbLightsLocation, (GLint)_lights.size());

    GLint lightsLocation = glGetUniformLocation(_lightingPass.getProgram(), "lights");
    glProgramUniform3fv(_lightingPass.getProgram(), lightsLocation, _lights.size(),
                                  glm::value_ptr(_lights[0]));


    glUniformMatrix4fv( glGetUniformLocation(_lightingPass.getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(_lightingPass.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

    GLint cameraPositionLocation = glGetUniformLocation(_lightingPass.getProgram(), "cameraPosition");
    glm::vec3 cp = _camera->position();
    glProgramUniform3f(_lightingPass.getProgram(), cameraPositionLocation, cp[0], cp[1], cp[2]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _gBuff.getGPosition());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _gBuff.getGNormal());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _gBuff.getGAlbedo());
    glActiveTexture(GL_TEXTURE3); // add extra SSAO texture to lighting pass
    glBindTexture(GL_TEXTURE_2D, _ssaoBlurBuff.getSSAOColorBufferBlur());
    renderQuad();*/

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
    //ObjParser::parse(std::string("Models/cat.obj"), &_3DObjects, true);
    //ObjParser::parse(std::string("Models/cat.obj"), &_3DObjects, true);
    //ObjParser::parse(std::string("Models/cat.obj"), &_3DObjects, true);
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
    /*Bspline test = Bspline (std::vector<glm::vec3>{glm::vec3(-1, 0, 1.3), glm::vec3(0, 1, 1.3), glm::vec3(1, 0, 1.3), glm::vec3(2,1,1.3), glm::vec3(3, 1, 1.3)},3);
    glm::vec3 v;
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
    /*BsplinePatch test = BsplinePatch (glm::vec3(-2,-4,-8),glm::vec3(0.1,0.4,0.8),3);
    for (int i = 0; i < 11; i ++ ) {
        Bspline b1 = Bspline (std::vector<glm::vec3>{glm::vec3(0,0,i), glm::vec3(1,1,i), glm::vec3(0,2,i), glm::vec3(2,3,i), glm::vec3(2,4,i), glm::vec3(1,5,i)},3);
        test.addControlPoly(b1);
    }

    test.eval(0.02,0.02);
    _3DObjects.push_back(test);*/


    // Initialise geometric data
    /*std::vector<GLfloat> vertices = {
        1.f, 1.f, 0.0f,     // 0
        2.f, 1.f, 0.0f,     // 1
        3.f, 1.f, 0.0f,     // 2
        1.5f, 2.f, 0.0f,    // 3
        2.5f, 2.f, 0.0f,    // 4
        1.f, 3.f, 0.0f,     // 5
        2.f, 3.f, 0.0f,     // 6
        3.f, 3.f, 0.0f,     // 7
        0.5f, 2.f, 0.0f,     // 8
        3.5f, 2.f, 0.0f,     // 9
        1.5f, 4.f, 0.0f,     // 10
        2.5f, 4.f, 0.0f,     // 11

    };
    std::vector<GLuint> indices = {
        // Note that we start from 0!
        0, 3, 1,    // 0
        1, 3, 4,    // 1
        1, 4, 2,    // 2
        3, 5, 6,    // 3
        3, 6, 4,    // 4
        4, 6, 7,    // 5
        0, 8, 3,    // 6
        8, 5, 3,    // 7
        2, 4, 9,    // 8
        4, 7, 9,    // 9
        5, 10, 6,    // 10
        6, 10, 11,    // 11
        6, 11, 7,    // 12
    };
    Material3DObject so = Material3DObject(glm::vec3(0.f,0.f,0.f), glm::vec3(0.7,0.2,0.3));
    MeshManager m = MeshManager ();
    so.getIndices() = indices;
    so.getVertices() = vertices;
    m.useMaterial3DObject(so);
    m.subdivide();
    std::cout << "strat converting" << std::endl;
    m.convertToMaterial3DObject(so);
    std::cout << "Vertices :" << std::endl;
    for (unsigned int i = 0; i < so.getVertices().size(); i+=3){
        std::cout << so.getVertices()[i] << " / " << so.getVertices()[i+1] << " / " << so.getVertices()[i+2] << std::endl;
    }
    std::cout << "Indices :" << std::endl;
    for (unsigned int i = 0; i < so.getIndices().size(); i+=3){
        std::cout << so.getIndices()[i] << " / " << so.getIndices()[i+1] << " / " << so.getIndices()[i+2] << std::endl;
    }
    std::cout << "Normals :" << std::endl;
    for (unsigned int i = 0; i < so.getNormals().size(); i+=3){
        std::cout << so.getNormals()[i] << " / " << so.getNormals()[i+1] << " / " << so.getNormals()[i+2] << std::endl;
    }
    _3DObjects.push_back(so);*/
    /*MeshManager m = MeshManager ();
    m.useMaterial3DObject(_3DObjects[0].getMeshes()[0]);
    m.subdivide();
    m.convertToMaterial3DObject(_3DObjects[0].getMeshes()[0]);
    m.subdivide();
    m.convertToMaterial3DObject(_3DObjects[2].getMeshes()[0]);
    m.useMaterial3DObject(_3DObjects[3].getMeshes()[0]);
    m.subdivide();
    m.simplificationHEC(5000);
    m.convertToMaterial3DObject(_3DObjects[3].getMeshes()[0]);

    _3DObjects[1].translate(glm::vec3(3,0,0));
    _3DObjects[2].translate(glm::vec3(-3,0,0));
    _3DObjects[3].translate(glm::vec3(-3,-3,0));*/
    GL_CHECK_ERROR
    ObjectLoader ol = ObjectLoader("Models/Sponza");
    if (ol.objLoader("sponza2.dae")) {
        GL_CHECK_ERROR
        _3DObjects.push_back(ol.getObj());
        GL_CHECK_ERROR
        _3DObjects[0].setColor(glm::vec3(0.1f, 0.5f, 0.7f));
    }
    GL_CHECK_ERROR
    /*for (unsigned int i = 0; i<_3DObjects[0].getMeshes().size(); i++) {
        MeshManager m = MeshManager ();
        m.useMaterial3DObject(_3DObjects[0].getMeshes()[i]);
        m.subdivide();
        m.simplificationHEC(5000);
        m.convertToMaterial3DObject(_3DObjects[0].getMeshes()[i]);
    }
    _3DObjects[0].translate(glm::vec3(1,0,0));
    _3DObjects[1].translate(glm::vec3(-1,0,0));*/
    /*MeshManager m = MeshManager();
    m.useMaterial3DObject(_3DObjects[0].getMeshes()[0]);
    m.convertToMaterial3DObject(_3DObjects[0].getMeshes()[0]);*/
    GL_CHECK_ERROR
    _nb3DObjects = _3DObjects.size();
    for (unsigned int i = 0; i < _nb3DObjects; i++) {
        _3DObjects[i].setupGL();
    }
    GL_CHECK_ERROR
}

void Scene3DObject::initQuad() {
    float quadVertices[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &_quadVAO);
    glGenBuffers(1, &_quadVBO);
    glBindVertexArray(_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

void Scene3DObject::initSamples () {
    std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.f); // generates random floats between 0.0 and rayon
    std::default_random_engine generator;
    for (unsigned int i = 0; i < 64; ++i)
    {
        glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);
        float scale = float(i) / 64.0;

        // scale samples s.t. they're more aligned to center of kernel
        scale = lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        _ssaoKernel.push_back(sample);
    }
}

void Scene3DObject::initNoise () {
    GL_CHECK_ERROR
    std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.f); // generates random floats between 0.0 and rayon
    std::default_random_engine generator;

    for (unsigned int i=0; i < 16; i++) {
        glm::vec3 noise(randomFloats(generator) * 2.f - 1.f, randomFloats(generator) * 2.f - 1.f, 0.f);
        _ssaoNoise.emplace_back(noise);
    }
    GL_CHECK_ERROR
    //glGenTextures(1, &_noiseTexture);
    glBindTexture(GL_TEXTURE_2D, _noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &_ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GL_CHECK_ERROR
}

void Scene3DObject::renderQuad () {
    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

