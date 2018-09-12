#include "scene.h"
#include <iostream>


Scene::Scene(int width, int height) : _width(width), _height(height), _drawfill(true) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    //glFrustum(-1000,1000,-1000,1000,0.5,300);
}

Scene::~Scene() {

}

void Scene::resize(int width, int height) {
   _width = width;
   _height = height;
   glViewport(0, 0, width, height);
}

void Scene::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    if (_drawfill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Scene::mouseclick(int , float , float ) {

}

void Scene::mousemove(float , float ) {

}

void Scene::keyboardmove(int , double ) {

}

bool Scene::keyboard(unsigned char) {
    return false;
}

void Scene::toggledrawmode() {
    _drawfill = !_drawfill;
}

