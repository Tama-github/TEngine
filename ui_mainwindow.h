/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Version_OpenGL;
    QAction *actionHello_triangle;
    QAction *actionHello_camera;
    QAction *actionHello_spheres;
    QAction *actionHello_clear;
    MyOpenGLWidget *openglWidget;
    QMenuBar *menuBar;
    QMenu *menuInfo;
    QMenu *menu_Demo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 656);
        action_Version_OpenGL = new QAction(MainWindow);
        action_Version_OpenGL->setObjectName(QStringLiteral("action_Version_OpenGL"));
        actionHello_triangle = new QAction(MainWindow);
        actionHello_triangle->setObjectName(QStringLiteral("actionHello_triangle"));
        actionHello_camera = new QAction(MainWindow);
        actionHello_camera->setObjectName(QStringLiteral("actionHello_camera"));
        actionHello_spheres = new QAction(MainWindow);
        actionHello_spheres->setObjectName(QStringLiteral("actionHello_spheres"));
        actionHello_clear = new QAction(MainWindow);
        actionHello_clear->setObjectName(QStringLiteral("actionHello_clear"));
        openglWidget = new MyOpenGLWidget(MainWindow);
        openglWidget->setObjectName(QStringLiteral("openglWidget"));
        openglWidget->setMinimumSize(QSize(800, 600));
        MainWindow->setCentralWidget(openglWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QStringLiteral("menuInfo"));
        menu_Demo = new QMenu(menuBar);
        menu_Demo->setObjectName(QStringLiteral("menu_Demo"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Demo->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuInfo->addAction(action_Version_OpenGL);
        menu_Demo->addAction(actionHello_clear);
        menu_Demo->addAction(actionHello_triangle);
        menu_Demo->addAction(actionHello_camera);
        menu_Demo->addAction(actionHello_spheres);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hello OpenGL ...", 0));
        action_Version_OpenGL->setText(QApplication::translate("MainWindow", "&Version OpenGL", 0));
        actionHello_triangle->setText(QApplication::translate("MainWindow", "Hello triangle ...", 0));
        actionHello_camera->setText(QApplication::translate("MainWindow", "Hello camera ...", 0));
        actionHello_spheres->setText(QApplication::translate("MainWindow", "Hello spheres ...", 0));
        actionHello_clear->setText(QApplication::translate("MainWindow", "Hello clear ...", 0));
        menuInfo->setTitle(QApplication::translate("MainWindow", "Info", 0));
        menu_Demo->setTitle(QApplication::translate("MainWindow", "&Demo", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
