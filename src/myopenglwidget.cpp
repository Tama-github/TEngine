#include "myopenglwidget.h"

#include <QMessageBox>
#include <QApplication>
#include <QDateTime>

#include <iostream>
#include <stdexcept>

#include "hello_triangles/hellotriangles.h"
#include "hello_camera/hellocamera.h"
#include "hello_spheres/hellospheres.h"
#include "hello_3dObjScene/Scene3DObjects.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :QGLWidget(parent), _scene(nullptr), _lastime(0) {
    // add all demo constructors here
    _democonstructors.push_back( [](int width, int height)->Scene*{std::cout << "Hello clear ..." << std::endl; return new Scene(width, height);} );
    _democonstructors.push_back( [](int width, int height)->Scene*{std::cout << "Hello triangles ..." << std::endl; return new SimpleTriangle(width, height);} );
    _democonstructors.push_back( [](int width, int height)->Scene*{std::cout << "Hello camera ..." << std::endl; return new SimpleCamera(width, height);} );
    _democonstructors.push_back( [](int width, int height)->Scene*{std::cout << "Hello spheres ..." << std::endl; return new SimpleSpheres(width, height);} );
    _democonstructors.push_back( [](int width, int height)->Scene*{std::cout << "Hello 3D Object ..." << std::endl; return new Scene3DObject(width, height);} );

    //Animation
    _animation_timer = new QTimer(this);
    //start animation loop
    connect(_animation_timer, SIGNAL(timeout()), this, SLOT(on_animation_timer()));
    _animation_timer->start(1000.0/60.0);
}

MyOpenGLWidget::~MyOpenGLWidget() {
    delete (_animation_timer);
}

void MyOpenGLWidget::initializeGL() {
    // Initialize OpenGL and all OpenGL dependent stuff below
    //initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    _scene.reset(_democonstructors[0](width(), height()));
}

void MyOpenGLWidget::paintGL() {
    std::int64_t starttime = QDateTime::currentMSecsSinceEpoch();
    _scene->draw();
    glFinish();
    std::int64_t endtime = QDateTime::currentMSecsSinceEpoch();
    _lastime = endtime-starttime;
}

void MyOpenGLWidget::resizeGL(int width, int height) {
    _scene->resize(width, height);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
    // buttons are 0(left), 1(right) to 2(middle)
    int b;
    Qt::MouseButton button=event->button();
    if (button & Qt::LeftButton) {
        if ((event->modifiers() & Qt::ControlModifier))
            b = 2;
        else
            b = 0;
    } else if (button & Qt::RightButton)
        b = 1;
    else if (button & Qt::MiddleButton)
        b = 2;
    else
        b=3;
    _scene->mouseclick(b, event->x(), event->y());
    _lastime = QDateTime::currentMSecsSinceEpoch();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    _scene->mousemove(event->x(), event->y());
    //update();
}

void MyOpenGLWidget::on_animation_timer () {
    //_scene->draw();
    //std::cout << "alo" << std::endl;
    //_animation_timer->start(1000.0/60.0);
    update();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        // Demo keys
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            activatedemo(event->key()-Qt::Key_0);
        break;
        // Move keys
        case Qt::Key_Left:
        case Qt::Key_Up:
        case Qt::Key_Right:
        case Qt::Key_Down:
            _scene->keyboardmove(event->key()-Qt::Key_Left, 1./100/*double(_lastime)/10.*/);
            //update();
        break;
        // Wireframe key
        case Qt::Key_W:
            _scene->toggledrawmode();
            //update();
        break;
        // Other keys are transmitted to the scene
        default :
            if (_scene->keyboard(event->text().toStdString()[0]))
                //update();
        break;
    }
}

void MyOpenGLWidget::activatedemo(unsigned int numdemo) {
    if (numdemo < _democonstructors.size()) {
        std::cout << "Activating demo " << numdemo << " : ";
        makeCurrent();
        _scene.reset(_democonstructors[numdemo](width(), height()));
        doneCurrent();
        update();
    }
}

