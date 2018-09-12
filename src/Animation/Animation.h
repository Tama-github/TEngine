#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <functional>

#include "../opengl_stuff.h"

class Animation {
public:
    Animation ();
    ~Animation ();

    void addTranslation (const glm::vec3& translation);
    void addRotation (const float& angle, const glm::vec3& dirr);
    void addScaling (const glm::vec3& scale);
    glm::mat4 playAnimation (const glm::mat4& model);

private:
    std::vector< std::function<glm::mat4 (glm::mat4)> > _animations;

};

#endif
