#ifndef GLWIDGET_H
#define GLWIDGET_H

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
#include "mesh/billboard.h"
#include "mesh/particules.h"
#include "camera.h"

#include <QCoreApplication>
#include <QSet>
#include <string>
#include <vector>
#include <QDebug>
#include <random>

using namespace std;

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
	QOpenGLShaderProgram program, billboard;

	QVector2D mousePressPosition;
	QVector3D rotationAxis;
	qreal angularSpeed;
	QQuaternion rotation;

	Billboard* bil;
	Cube* cube;

	Camera camera;

	vector<Shape3D> shape;
	vector<Particules> bill;

	int lastUpdate, frameCounter, lastFrameTime;

	QSet<int> keysPressed;
};

#endif // GLWIDGET_H
