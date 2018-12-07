#ifndef BONE_H
#define BONE_H

#include "../opengl_stuff.h"
#include "../Animation/Animation.h"

#include <vector>
#include <cmath>

class Bone
{
public:
    Bone ();
    Bone (glm::vec3 position);
    Bone (Bone* parent, glm::vec3 position);

    void translate (glm::vec3 translate);
    void rotate (float angle, glm::vec3 direction);
    void scale (glm::vec3 scale);
    void addChild (Bone* newChild);
    void setIdx (unsigned int idx);
    Bone* ith (unsigned int idx);
    unsigned int getIdx();
    void setTransform(glm::mat4 t);
    glm::mat4 getTransform();
    glm::mat4 getRestPositionInv();
    glm::vec3 getPosition();

    std::vector<GLfloat> wheightComputing(std::vector<GLfloat> vertices);

    /* Animation actions for the bone */
    //Animation& getAnimation();
    //void playAnimation();


private:
    Bone* _parent;
    std::vector<Bone*> _children;
    glm::mat4 _transform;
    glm::mat4 _restPosition;
    glm::mat4 _restPositionInv;
    glm::vec3 _position;
    unsigned int _idx;

    //Animation _animation;


};

#endif // BONE_H
