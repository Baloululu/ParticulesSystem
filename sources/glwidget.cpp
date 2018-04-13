#include "../includes/glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	geometries(0),
	angularSpeed(0),
	log(),
	camera()
{
}

GLWidget::~GLWidget()
{
	// Make sure the context is current when deleting the texture
	// and the buffers.
	makeCurrent();
	delete geometries;
	delete shape;
	doneCurrent();
}

//! [0]
void GLWidget::mousePressEvent(QMouseEvent *e)
{
	// Save mouse press position
	mousePressPosition = QVector2D(e->localPos());
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
	// Mouse release position - mouse press position
	QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

	// Rotation axis is perpendicular to the mouse position difference
	// vector
	QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

	// Accelerate angular speed relative to the length of the mouse sweep
	qreal acc = diff.length() / 100.0;

	// Calculate new rotation axis as weighted sum
	rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

	// Increase angular speed
	angularSpeed += acc;
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
//	if (event->key() == Qt::Key_Up)
	log.info("blabla");
}

void GLWidget::timerEvent(QTimerEvent *)
{
	// Decrease angular speed (friction)
	angularSpeed *= 0.99;

	// Stop rotation when speed goes below threshold
	if (angularSpeed < 0.01) {
		angularSpeed = 0.0;
	} else {
		// Update rotation
		rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
		// Request an update
	}
	update();
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
	glEnable(GL_CULL_FACE);
	//! [2]

	geometries = new GeometryEngine;

	shape = new Shape3D("cube", new Cube(), Transform());

	camera.moveTo(0,0,-7);

	frameCount = 0;
	lastUpdate = 0;

	// Use QBasicTimer because its faster than QTimer
	timer.start(1000/60, this);
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
}


void GLWidget::resizeGL(int w, int h)
{
	camera.calculateProjection(w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.setUniformValue("mvp", camera.cameraMatrix());
	shape->draw(&program);

	++frameCount;

	if (fps.elapsed() - lastUpdate > 1000)
	{
		float temp = (fps.elapsed() - lastUpdate) / 1000;
		log.info(std::to_string(frameCount / temp).c_str());
		frameCount = 0;
		lastUpdate = fps.elapsed();
	}
}
