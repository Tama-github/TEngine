#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "opengl_stuff.h"
#include "Materials/light.h"

/** Simple classe for managing an OpenGL scene
 */
class Scene {

public:
    explicit Scene(int width, int height);
    virtual ~Scene();

    virtual void resize(int width, int height);
    virtual void draw();

    virtual void mouseclick(int button, float xpos, float ypos);
    virtual void mousemove(float xpos, float ypos);
    virtual void keyboardmove(int key, double time);
    virtual bool keyboard(unsigned char k);


    void toggledrawmode();

protected:
    // Width and heigth of the viewport
    int _width;
    int _height;

private:
    // Rendering mode (true is filled, false is wireframed
    bool _drawfill;

};


#endif // SCENE_H
