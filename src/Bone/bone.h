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
    Bone (unsigned int idx);

    //void translate (glm::vec3 translate);
    //void rotate (float angle, glm::vec3 direction);
    //void scale (glm::vec3 scale);
    //void setChild (Bone* child);
    //void setIdx (unsigned int idx);
    //Bone* ith (unsigned int idx);
    std::vector<GLfloat> wheightComputing(std::vector<GLfloat> vertices);



    /* Animation actions for the bone */
    //Animation& getAnimation();
    //void playAnimation();
    Bone* _parent;
    Bone* _children;
    glm::mat4 _transform;
    glm::mat4 _offset;
    glm::vec3 _position;
    glm::vec3 _direction;
    float _length;
    unsigned int _idx;


};

#endif // BONE_H
