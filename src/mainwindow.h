#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>

#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QOpenGLWindow>


#include <QMessageBox>

#include <iostream>
#include <sstream>
#include <iomanip>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Version_OpenGL_triggered();

    void on_actionHello_triangle_triggered();

    void on_actionHello_camera_triggered();

    void on_actionHello_spheres_triggered();

    void on_actionHello_clear_triggered();

private:
    Ui::MainWindow *ui;
    QSurfaceFormat format;
    QWidget *parent;
    QOpenGLContext *context;
    QOpenGLFunctions *f;
};

#endif // MAINWINDOW_H
