#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
	QOpenGLWidget(parent),
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
	delete bil;
	delete cube;
	delete plan;

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
	}

	for (vector<ParticuleSystem>::iterator it = bill.begin(); it != bill.end(); ++it)
	{
		it->computeAnimation(temp, &computeProgramme, camera.getPosition());
	}

	update();
	frameCounter++;

	float checkSecond = fps.elapsed() - lastFrameTime;

	if (checkSecond > 1000)
	{
		qDebug() << checkSecond / float(frameCounter) << "ms/frame or" << float(frameCounter) * 1000 / checkSecond << "fps";
		frameCounter = 0;
		lastFrameTime = fps.elapsed();
	}
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

	// Compile vertex shader
	if (!billboard.addShaderFromSourceFile(QOpenGLShader::Vertex, "../ParticulesSystem/vbillboard.vsh"))
		close();

	// Compile fragment shader
	if (!billboard.addShaderFromSourceFile(QOpenGLShader::Fragment, "../ParticulesSystem/fshader.fsh"))
		close();

	// Link shader pipeline
	if (!billboard.link())
		close();

	if (!computeProgramme.addShaderFromSourceFile(QOpenGLShader::Compute, "../ParticulesSystem/compute.cs"))
		close();

	if (!computeProgramme.link())
		close();
}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();

	glClearColor(0, 0, 0.5, 1);

	initShaders();

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// Enable back face culling
	glEnable(GL_CULL_FACE);
//	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	QVector3D billScale = QVector3D(1, 1, 1);
	QQuaternion rot = QQuaternion::fromAxisAndAngle(0, 0, 1, 0);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> col(0.7f, 1.0f);

	bil = new Billboard(8, 0.02, QVector4D(col(gen), col(gen), col(gen), 1.0f) );
	cube = new Cube();
	plan = new Plan();

	bill.push_back( ParticuleSystem("Particules", bil, Transform(QVector3D(0, 0, 0), billScale, rot), 50000) );

//	shape.push_back( Shape3D("Cube", cube, Transform()) );
	shape.push_back( Shape3D("Plan", plan, Transform(QVector3D(0, 0, 0), QVector3D(5, 5, 1), QQuaternion::fromAxisAndAngle(0, 0, 1, 0))) );

//	shape.push_back( Shape3D("Billboard", bil, Transform()) );

	camera.moveTo(7,0,7);
	camera.loockAt(QVector3D(0, 0, 2));

	lastUpdate = 0;
	lastFrameTime = 0;
	frameCounter = 0;

	// Use QBasicTimer because its faster than QTimer
	timer.start(1000.0/60.0, this);
//	timer.start(0, this);
	fps.start();
}

void GLWidget::resizeGL(int w, int h)
{
	camera.calculateProjection(w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (shape.size() > 0)
	{
		if (!program.bind())
			close();

		program.setUniformValue("mvp", camera.cameraMatrix());

		for (vector<Shape3D>::iterator it = shape.begin(); it != shape.end(); ++it)
		{
			it->draw(&program);
		}
	}

	if (bill.size() > 0)
	{
		if (!billboard.bind())
			close();

		billboard.setUniformValue("mvp", camera.cameraMatrix());
		billboard.setUniformValue("cameraRight", QVector3D::crossProduct(camera.getDir(), camera.getUp()));
		billboard.setUniformValue("cameraUp", camera.getUp());

		for (vector<ParticuleSystem>::iterator it = bill.begin(); it != bill.end(); ++it)
		{
			it->draw(&billboard, &camera);
		}
	}
}
