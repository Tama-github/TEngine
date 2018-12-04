#ifndef SCENE3DOBJECT_H
#define SCENE3DOBJECT_H

#include <memory>
#include <QTimer>
#include <QGraphicsScene>
#include <random>

#include "scene.h"

#include "../hello_camera/camera.h"
#include "../ShaderManager/shadermanager.h"

/* 3D Objects */
#include "../Materials/spheres.h"
#include "../Materials/material3DObject.h"
#include "../Materials/composed3dobject.h"

/* Bones/Skeletaon/Animation */
#include "../Bone/bone.h"

/* Import 3D Models */
#include "../3DObjectParser/objparser.h"
#include "../3DObjectParser/objectloader.h"
#include "../Materials/Imported3DModel.h"

/* B-Splines */
#include "../Materials/bspline.h"
#include "../Materials/bsplinepatch.h"

/* Geometry operations on meshes */
#include "../MeshManager/meshmanager.h"

/*Test Frame buffer*/
#include "../RenderObject/testbuffer.h"

/* SSAO */
#include "../RenderObject/gbuffer.h"
#include "../RenderObject/ssaobuffer.h"
#include "../RenderObject/ssaoblurbuffer.h"


class Scene3DObject : public Scene {

public:
    explicit Scene3DObject(int width, int height);
    ~Scene3DObject();

    void resize(int width, int height) override;
    void draw() override;

    void mouseclick(int button, float xpos, float ypos) override;
    void mousemove(float xpos, float ypos) override;
    void keyboardmove(int key, double time) override;
    bool keyboard(unsigned char k) override;

private:
    //Objects
    std::vector<Composed3DObject> _3DObjects;
    unsigned int _nb3DObjects;

    // A simple geometry
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _normals;
    std::vector<GLuint> _indices;

    //frame buffers
    //unsigned int _fbo;

    //render buffers
    //unsigned int _rbo;

    //screen shaders
    //ShaderManager _screenShader;

    //Lights
    std::vector<glm::vec3> _lights;

    // Shader program for rendering
    unsigned int _activeshader;
    std::vector<ShaderManager> _shaderselector;

    // Different availableprograms
    //GLuint _programcolor;
    //GLuint _programnormal;

    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

    using CameraSelector=std::function<Camera*()>;
    std::vector<CameraSelector> _cameraselector;
    int _activecamera;

    std::unique_ptr<Camera> _camera;

    // matrices
    //glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;

    //quad
    unsigned int _quadVAO, _quadVBO;

    //test frame buffer
    TestBuffer _tbuff;

    //SSAO
    GBuffer _gBuff;
    SSAOBuffer _ssaoBuff;
    SSAOBlurBuffer _ssaoBlurBuff;
    float _rayon;
    //std::vector<glm::vec3> _ssaoKernel;
    //std::vector<glm::vec3> _ssaoNoise;
    //unsigned int _noiseTexture;
    ShaderManager _geometryPass;
    ShaderManager _lightingPass;

    // Initilizations
    void init3DObjects ();
    void initQuad ();
    //void initSamples ();
    //void initNoise ();

    void drawScene ();
    void drawFrameBuffer ();
    void drawSSAO ();

    void renderQuad();

};

/*------------------------------------------------------------------------------------------------------------------------*/


#endif // SIMPLESPHERES_H
