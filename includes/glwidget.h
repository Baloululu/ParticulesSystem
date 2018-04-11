#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QTime>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <math.h>
#include "mesh/shape3d.h"
#include "mesh/cube.h"

#include <QMessageLogger>
#include <QCoreApplication>
#include <string>

class GeometryEngine;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QBasicTimer timer;
    QTime fps;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

    QVector3D cameraPos, target, cameraDir, up, cameraRight, cameraUp;
    QMatrix4x4 view;

    Shape3D *shape;

    int frameCount, lastUpdate;

    QMessageLogger log;
};

#endif // GLWIDGET_H
