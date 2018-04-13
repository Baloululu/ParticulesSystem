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
    sources/geometryengine.cpp \
    sources/glwidget.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/mesh/cube.cpp \
    sources/mesh/mesh.cpp \
    sources/mesh/shape3d.cpp \
    sources/mesh/transform.cpp \
    sources/camera.cpp

HEADERS += \
    includes/geometryengine.h \
    includes/glwidget.h \
    includes/mainwindow.h \
    includes/mesh/cube.h \
    includes/mesh/mesh.h \
    includes/mesh/shape3d.h \
    includes/mesh/struct.h \
    includes/mesh/transform.h \
    includes/camera.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    fshader.fsh \
    vshader.vsh
