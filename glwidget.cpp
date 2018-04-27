#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	geometries(0),
	angularSpeed(0),
	camera()
{
	this->setFocusPolicy(Qt::StrongFocus);
	camera.setSpeed(3);
}

GLWidget::~GLWidget()
{
	// Make sure the context is current when deleting the texture
	// and the buffers.
	makeCurrent();
	delete geometries;
	doneCurrent();
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	keysPressed += event->key();
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	keysPressed -= event->key();
}

void GLWidget::timerEvent(QTimerEvent *)
{
	float temp = (fps.elapsed() - lastUpdate) / 1000.0;
	lastUpdate = fps.elapsed();
	if (keysPressed.count() > 0)
	{
		QVector3D move = QVector3D(0, 0, 0);
		float roulis = 0, tangage = 0, lacet = 0;

		if (keysPressed.contains(Qt::Key_Z))
			move += camera.getDir();
		else if (keysPressed.contains(Qt::Key_S))
			move -= camera.getDir();

		if (keysPressed.contains(Qt::Key_Shift))
			move += camera.getUp();
		else if (keysPressed.contains(Qt::Key_Control))
			move -= camera.getUp();

		if (keysPressed.contains(Qt::Key_Q))
			move += QVector3D::crossProduct(camera.getUp(), camera.getDir());
		else if (keysPressed.contains(Qt::Key_D))
			move -= QVector3D::crossProduct(camera.getUp(), camera.getDir());

		if (keysPressed.contains(Qt::Key_Up))
			tangage -= 15;
		else if (keysPressed.contains(Qt::Key_Down))
			tangage += 15;

		if (keysPressed.contains(Qt::Key_Left))
			lacet += 15;
		else if (keysPressed.contains(Qt::Key_Right))
			lacet -= 15;

		if (keysPressed.contains(Qt::Key_A))
			roulis -= 10;
		else if (keysPressed.contains(Qt::Key_E))
			roulis += 10;

		if (!move.isNull())
		{
			move.normalize();
			camera.move(move * temp * camera.getSpeed());
		}

		if (tangage)
			camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(camera.getUp(), camera.getDir()), temp * tangage * camera.getSpeed()));
		if(roulis)
			camera.rotate(QQuaternion::fromAxisAndAngle(camera.getDir(), temp * roulis * camera.getSpeed()));
		if(lacet)
			camera.rotate(QQuaternion::fromAxisAndAngle(camera.getUp(), temp * lacet * camera.getSpeed()));

		update();
	}
}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();

	glClearColor(0, 0, 0, 1);

	initShaders();

	//! [2]
	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// Enable back face culling
//	glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	//! [2]

	geometries = new GeometryEngine;

	QVector3D billPos = QVector3D(0, 0, 8), billScale = QVector3D(1, 1, 1);
	QQuaternion rot = QQuaternion::fromAxisAndAngle(0, 0, 1, 0);

	shape.push_back( Shape3D("Cube", new Cube(), Transform()) );
	shape.push_back( Shape3D("Billboard", new Billboard(8), Transform(billPos, billScale, rot)) );

	camera.moveTo(0,0,-7);

	lastUpdate = 0;

	// Use QBasicTimer because its faster than QTimer
	timer.start(1000.0/60.0, this);
	//    timer.start(0, this);
	fps.start();
}

void GLWidget::initShaders()
{
	// Compile vertex shader
	if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../ParticulesSystem/vshader.vsh"))
		close();

	// Compile fragment shader
	if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../ParticulesSystem/fshader.fsh"))
		close();

	// Link shader pipeline
	if (!program.link())
		close();

	// Bind shader pipeline for use
	if (!program.bind())
		close();

	// Compile vertex shader
	if (!billboard.addShaderFromSourceFile(QOpenGLShader::Vertex, "../ParticulesSystem/vbillboard.vsh"))
		close();

	// Compile fragment shader
	if (!billboard.addShaderFromSourceFile(QOpenGLShader::Fragment, "../ParticulesSystem/fshader.fsh"))
		close();

	// Link shader pipeline
	if (!billboard.link())
		close();

	// Bind shader pipeline for use
	if (!billboard.bind())
		close();
}

void GLWidget::resizeGL(int w, int h)
{
	camera.calculateProjection(w, h);
}

void GLWidget::paintGL()
{
	if (!program.bind())
		close();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.setUniformValue("mvp", camera.cameraMatrix());

	shape[0].draw(&program);

	if (!billboard.bind())
		close();

	billboard.setUniformValue("mvp", camera.cameraMatrix());
	billboard.setUniformValue("cameraRight", QVector3D::crossProduct(camera.getDir(), camera.getUp()));
	billboard.setUniformValue("cameraUp", camera.getUp());

	shape[1].draw(&billboard);
}
