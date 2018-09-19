#ifndef SCENE3DOBJECT_H
#define SCENE3DOBJECT_H

#include <memory>
#include <QTimer>
#include <QGraphicsScene>

#include "scene.h"

#include "../hello_camera/camera.h"
#include "../ShaderManager/shadermanager.h"

#include "../Materials/spheres.h"
#include "../Materials/material3DObject.h"
#include "../3DObjectParser/objparser.h"
#include "../Materials/Imported3DModel.h"
#include "../Materials/bspline.h"
#include "../Materials/bsplinepatch.h"


/** Spheres : different ways of building and rendering spheres
 * Objectifs des travaux pratiques :
 *  En vous fondant sur le tutoriel learnopengl.com vous completerez/modifierez/dupliquerez cette démo pour réaliser les tâches suivantes :
 *      1) Construire le maillage d'une sphère selon les 2 méthodes
 *          a) UV_SPHERE : Construction par maillage du domaine paramétrique de définiton de la sphère
 *          b) ICO_SPHERE : Construction par subdivision d'un icosaèdre (fr.wikipedia.org/wiki/icosaèdre)
 *      2) Visualiser la sphere avec un éclairage 3 points (fr.wikipedia.org/wiki/Éclairage_trois_points)
 *          et un matériau de type Blinn-Phong dont les paramètres seront définis par une ou plusieurs textures.
 *      3) Visualiser la sphère avec une couleur proportionelle à l'erreur d'approximation par rapport
 *          à la définition analytique de la sphère.
 *      4) BONUS : permettre le chargement et la visualisation avec un éclairage 3 points d'une géométrie définie
 *          par un fichier au format obj/mtl (en.wikipedia.org/wiki/Wavefront_.obj_file). Des données sont accessibles
 *          sur le site http://tf3dm.com/3d-models/all
 *
 * Evaluationdes TPs :
 *  L'évaluation se fera par remise du code et des données nécessaires à l'exécution de la démo sous moodle. Si des dépendences
 *  ont été ajoutées, il n'est pas nécessaire de donner le code mais il faut préciser les noms et version des dépendances.
 *  Le code remis sera accompagné d'un document pdf expliquant les méthodes et algorithmes mis en oeuvre et proposant une analyse
 *  de l'erreur d'approximation dune sphère en fonction du nombre de triangles pour les deux représentations développées.
 *
 */
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
    std::vector<Material3DObject> _3DObjects;
    unsigned int _nb3DObjects;

    // A simple geometry
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _normals;
    std::vector<GLuint> _indices;

    //Lights
    std::vector<glm::vec3> _lights;

    // OpenGL object for geometry
    std::vector<GLuint> _vao;
    std::vector<GLuint> _vbo;
    std::vector<GLuint> _nbo;
    std::vector<GLuint> _ebo;

    // Shader program for rendering
    unsigned int _activeshader;
    std::vector<ShaderManager> _shaderselector;

    // Different availableprograms
    GLuint _programcolor;
    GLuint _programnormal;

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

    // Initilization of 3DObjects
    void init3DObjects ();

};

/*------------------------------------------------------------------------------------------------------------------------*/


#endif // SIMPLESPHERES_H
