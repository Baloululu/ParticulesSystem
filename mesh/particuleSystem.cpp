#include "particuleSystem.h"

ParticuleSystem::ParticuleSystem() : Shape3D(), n(10)
{
	init();
}

ParticuleSystem::ParticuleSystem(const ParticuleSystem& p) : Shape3D(p), n(p.n), part(p.part)
{
	initializeOpenGLFunctions();

	createBuffer();
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
//	posBuff.bind();
//	sort(part.begin(), part.end(), ParticuleCompare(cam->getPosition()));

//	auto ptr = posBuff.map(QOpenGLBuffer::WriteOnly);
//	memcpy(ptr, part.data(), part.size() * sizeof(Particule));
//	posBuff.unmap();
//	posBuff.release();

	program->setUniformValue("transform", transform.getCompute());

	mesh->bind();

	int vertexLocation = program->attributeLocation("position");
	int posLocation = program->attributeLocation("pos");
	int colLocation = program->attributeLocation("color");
	int lifeLocation = program->attributeLocation("life");

	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));

	glUseProgram(program->programId());

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glEnableVertexAttribArray(posLocation);
	glVertexAttribPointer(posLocation, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glEnableVertexAttribArray(colLocation);
	glVertexAttribPointer(colLocation, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, lifeBuffer);
	glEnableVertexAttribArray(lifeLocation);
	glVertexAttribPointer(lifeLocation, 1, GL_FLOAT, GL_FALSE, sizeof(float), 0);

	glVertexAttribDivisor(vertexLocation, 0); // particles vertices : always reuse the same vertices -> 0
	glVertexAttribDivisor(posLocation, 1); // position : one per particule
	glVertexAttribDivisor(colLocation, 1); // color : one per particule
	glVertexAttribDivisor(lifeLocation, 1); // life : one per particule

	glDrawElementsInstanced(GL_TRIANGLE_FAN, mesh->getIndicesNumber(), GL_UNSIGNED_SHORT, 0, nbActivePart);

	//reset glVertexAttribDivisor
	glVertexAttribDivisor(vertexLocation, 0);
	glVertexAttribDivisor(posLocation, 0);
	glVertexAttribDivisor(colLocation, 0);
	glVertexAttribDivisor(lifeLocation, 0);

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
	nbActivePart = 0;

//	random_device rd;
//	mt19937 gen(rd());
//	uniform_real_distribution<float> pos(-1, 1);
//	uniform_real_distribution<float> col(0.5, 1);
//	uniform_real_distribution<float> speed(0, 2);
//	uniform_real_distribution<float> angle(0, 2 * M_PI);
//	uniform_real_distribution<float> life(5, 10);

	for (int i = 0; i < n; ++i)
	{
//		id.push_back(i);
//		QVector4D position = QVector4D(0, 0, 0, 1);
//		QVector4D color = QVector4D(0, 1, 0, 1.0f);
//		float angle_temps = angle(gen);
//		QVector4D direction = QVector4D(cos(angle_temps) * speed(gen), sin(angle_temps) * speed(gen), 8, 0);
//		part.push_back(Particule(position, direction, color, life(gen)));
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

//	fillVec4Buffer(&positionBuffer, ParticuleAttribute::position);
//	fillVec4Buffer(&directionBuffer, ParticuleAttribute::direction);
//	fillVec4Buffer(&colorBuffer, ParticuleAttribute::color);
//	fillFloatBuffer(&lifeBuffer, ParticuleAttribute::life);
}

void ParticuleSystem::emitParticules(const float timePass)
{
	int nb = (int) (n * timePass)/7.0;

	int i = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> pos(-1, 1);
	uniform_real_distribution<float> col(0.5, 1);
	uniform_real_distribution<float> speed(0, 2);
	uniform_real_distribution<float> angle(0, 2 * M_PI);
	uniform_real_distribution<float> life(5, 10);

	while(nb > 0 && i < n)
	{
		if (part[i].getFloat(ParticuleAttribute::life) <= 0)
		{
			part[i].setVector(ParticuleAttribute::position, QVector4D(0, 0, 0, 1));
			part[i].setVector(ParticuleAttribute::color, QVector4D(0, 1, 0, 1.0f));
			float angle_temps = angle(gen);
			part[i].setVector(ParticuleAttribute::direction, QVector4D(cos(angle_temps) * speed(gen), sin(angle_temps) * speed(gen), 8, 0));
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
	std::sort(part.begin(), part.end());
	nbActivePart = 0;

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
