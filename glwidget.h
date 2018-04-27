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
#include "camera.h"

#include <QCoreApplication>
#include <QSet>
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

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void initShaders();
	void initTextures();

private:
	QBasicTimer timer;
	QTime fps;
	QOpenGLShaderProgram program;
	GeometryEngine *geometries;

	QVector2D mousePressPosition;
	QVector3D rotationAxis;
	qreal angularSpeed;
	QQuaternion rotation;

	Camera camera;

	Shape3D *shape;

	int lastUpdate;

	QSet<int> keysPressed;
};

#endif // GLWIDGET_H
