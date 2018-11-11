#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <iostream>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    QGLFormat format;
    format.setVersion(3, 3);
    format.setProfile(QGLFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QGLFormat::setDefaultFormat(format);

    ui->setupUi(this);

    ui->openglWidget->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_action_Version_OpenGL_triggered() {
    std::stringstream message;
    message << "Renderer       : " << glGetString(GL_RENDERER) << std::endl;
    message << "Vendor         : " << glGetString(GL_VENDOR) << std::endl;
    message << "Version        : " << glGetString(GL_VERSION) << std::endl;
    message << "GLSL Version   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    QMessageBox::information(this, "OpenGL Information", message.str().c_str());
}

void MainWindow::on_actionHello_clear_triggered() {
    ui->openglWidget->activatedemo(0);
}

void MainWindow::on_actionHello_triangle_triggered() {
    ui->openglWidget->activatedemo(1);
}

void MainWindow::on_actionHello_camera_triggered() {
    ui->openglWidget->activatedemo(2);
}

void MainWindow::on_actionHello_spheres_triggered() {
    ui->openglWidget->activatedemo(3);
}

