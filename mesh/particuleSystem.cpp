#include "particuleSystem.h"

ParticuleSystem::ParticuleSystem() : Shape3D(), n(10)
{
	init();
}

ParticuleSystem::ParticuleSystem(const ParticuleSystem& p) : Shape3D(p), n(p.n)
{
	init();
}

ParticuleSystem::ParticuleSystem(const string id, Mesh *m, const Transform t, const int nbParticules) : Shape3D(id, m, t), n(nbParticules)
{
	init();
}

ParticuleSystem::~ParticuleSystem()
{
}

void ParticuleSystem::draw(QOpenGLShaderProgram *program, const Camera* cam)
{
	program->setUniformValue("transform", transform.getCompute());

	mesh->bind();

	int vertexLocation = program->attributeLocation("position");
	int posLocation = program->attributeLocation("pos");
	int colLocation = program->attributeLocation("color");

	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));

	glUseProgram(program->programId());

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glEnableVertexAttribArray(posLocation);
	glVertexAttribPointer(posLocation, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glEnableVertexAttribArray(colLocation);
	glVertexAttribPointer(colLocation, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

	glVertexAttribDivisor(vertexLocation, 0); // particles vertices : always reuse the same vertices -> 0
	glVertexAttribDivisor(posLocation, 1); // position : one per particule
	glVertexAttribDivisor(colLocation, 1); // color : one per particule
	glDrawElementsInstanced(GL_TRIANGLE_FAN, mesh->getIndicesNumber(), GL_UNSIGNED_SHORT, 0, nbActivePart);

	//reset glVertexAttribDivisor
	glVertexAttribDivisor(vertexLocation, 0);
	glVertexAttribDivisor(posLocation, 0);
	glVertexAttribDivisor(colLocation, 0);

	mesh->release();
}

void ParticuleSystem::computeAnimation(const float timePass, QOpenGLShaderProgram *compute, const QVector4D cameraPosition)
{
//	qDebug("Compute : %d active particules", nbActivePart);
	readBuffer();
	emitParticules(timePass);
	sort();
	writeBuffer();
	physiqueCalculating(timePass, compute, cameraPosition);
}

void ParticuleSystem::init()
{
	initializeOpenGLFunctions();

	for (int i = 0; i < n; ++i)
	{
		part.push_back(Particule());
	}

	createBuffer();
}

void ParticuleSystem::createBuffer()
{
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, n * sizeof(Vec4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glGenBuffers(1, &directionBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, directionBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, n * sizeof(Vec4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colorBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, n * sizeof(Vec4), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glGenBuffers(1, &lifeBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, lifeBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, n * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glGenBuffers(1, &cameBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, cameBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, n * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticuleSystem::emitParticules(const float timePass)
{
	int nb = (int) (n * timePass)/(MAX_LIFE + MIN_LIFE);

	if (nbActivePart + nb > n)
	{
		qDebug("Maximum de particules atteind : actives : %d, generee : %d", nbActivePart, nb);
	}

	int i = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> speed(MIN_SPEED, MAX_SPEED);
	uniform_real_distribution<float> angle(-RANDOM_ANGLE, RANDOM_ANGLE);
	uniform_real_distribution<float> life(MIN_LIFE, MAX_LIFE);

	while(nb > 0 && i < n)
	{
		if (part[i].getFloat(ParticuleAttribute::life) <= 0)
		{
			part[i].setVector(ParticuleAttribute::position, QVector4D(0, 0, 0, 1));
			part[i].setVector(ParticuleAttribute::color, QVector4D(0, 1, 0, 1.0f));
			QVector3D dir = QVector3D(0, 0, 1);
			dir = dir * speed(gen);

			QQuaternion rot = QQuaternion::fromAxisAndAngle(1, 0, 0, angle(gen));
			dir = rot.rotatedVector(dir);
			rot = QQuaternion::fromAxisAndAngle(0, 1, 0, angle(gen));
			dir = rot.rotatedVector(dir);

			part[i].setVector(ParticuleAttribute::direction, dir.toVector4D());
			part[i].setFloat(ParticuleAttribute::life, life(gen));
			--nb;
		}
		++i;
	}
}

void ParticuleSystem::physiqueCalculating(const float timePass, QOpenGLShaderProgram *compute, const QVector4D cameraPosition)
{
	compute->bind();
	compute->setUniformValue("deltaTimeSec", timePass);
	compute->setUniformValue("maxLife", MAX_LIFE);
	compute->setUniformValue("cameraPosition", cameraPosition);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, directionBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, colorBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, lifeBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, cameBuffer);

	glUseProgram(compute->programId());
	glDispatchCompute((nbActivePart + 127.0)/128.0, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticuleSystem::sort()
{
	nbActivePart = 0;

	std::sort(part.begin(), part.end());

	while (nbActivePart < n && part[nbActivePart].getFloat(ParticuleAttribute::life) > 0) {
		++nbActivePart;
	}
}

void ParticuleSystem::readBuffer()
{
	readVec4Buffer(&positionBuffer, ParticuleAttribute::position);
	readVec4Buffer(&directionBuffer, ParticuleAttribute::direction);
	readVec4Buffer(&colorBuffer, ParticuleAttribute::color);
	readFloatBuffer(&lifeBuffer, ParticuleAttribute::life);
	readFloatBuffer(&cameBuffer, ParticuleAttribute::cameraDist);
}

void ParticuleSystem::writeBuffer()
{
	fillVec4Buffer(&positionBuffer, ParticuleAttribute::position);
	fillVec4Buffer(&directionBuffer, ParticuleAttribute::direction);
	fillVec4Buffer(&colorBuffer, ParticuleAttribute::color);
	fillFloatBuffer(&lifeBuffer, ParticuleAttribute::life);
	fillFloatBuffer(&cameBuffer, ParticuleAttribute::cameraDist);
}

void ParticuleSystem::fillVec4Buffer(GLuint *buffer, ParticuleAttribute attrib)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, *buffer);

	int bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
	Vec4 *buf = (Vec4 *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nbActivePart * sizeof(Vec4), bufMask);

	for (int i = 0; i < nbActivePart; ++i)
	{
		QVector4D temp = part[i].getVector(attrib);
		buf[i].x = temp.x();
		buf[i].y = temp.y();
		buf[i].z = temp.z();
		buf[i].w = temp.w();
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticuleSystem::fillFloatBuffer(GLuint *buffer, ParticuleAttribute attrib)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, *buffer);

	int bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
	float *buf = (float *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nbActivePart * sizeof(float), bufMask);

	for (int i = 0; i < nbActivePart; ++i)
	{
		buf[i] = part[i].getFloat(attrib);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticuleSystem::readFloatBuffer(GLuint *buffer, ParticuleAttribute attrib)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, *buffer);

	int bufMask = GL_MAP_READ_BIT;
	float *buf = (float *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nbActivePart * sizeof(float), bufMask);

	for (int i = 0; i < nbActivePart; ++i)
	{
		part[i].setFloat(attrib, buf[i]);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticuleSystem::readVec4Buffer(GLuint *buffer, ParticuleAttribute attrib)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, *buffer);

	int bufMask = GL_MAP_READ_BIT;
	Vec4 *buf = (Vec4 *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nbActivePart * sizeof(Vec4), bufMask);

	for (int i = 0; i < nbActivePart; ++i)
	{
		QVector4D temp;
		temp.setX(buf[i].x);
		temp.setY(buf[i].y);
		temp.setZ(buf[i].z);
		temp.setW(buf[i].w);
		part[i].setVector(attrib, temp);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
