QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/particles.cpp \
    src/force.cpp \
    src/particulesystem.cpp \
    src/particlecomputer.cpp \
    src/emitter.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/particles.h \
    src/force.h \
    src/particulesystem.h \
    src/particlecomputer.h \
    src/emitter.h \
    src/utilities.h

RESOURCES += \
    ressources/shaders.qrc \
