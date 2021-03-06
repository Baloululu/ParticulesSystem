#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T16:44:35
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = particules
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    mesh/cube.cpp \
    mesh/mesh.cpp \
    mesh/shape3d.cpp \
    mesh/transform.cpp \
    camera.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mesh/billboard.cpp \
    mesh/particuleSystem.cpp \
    mesh/particule.cpp \
    mesh/plan.cpp

HEADERS += \
    mesh/cube.h \
    mesh/mesh.h \
    mesh/shape3d.h \
    mesh/struct.h \
    mesh/transform.h \
    camera.h \
    glwidget.h \
    mainwindow.h \
    mesh/billboard.h \
    mesh/particuleSystem.h \
    mesh/particule.h \
    mesh/plan.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    fshader.fsh \
    vshader.vsh \
    vbillboard.vsh \
    compute.cs
