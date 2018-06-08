#include "particules.h"

Particules::Particules() : Shape3D(), n(10)
{
	init();
}

Particules::Particules(const Particules& p) : Shape3D(p), n(p.n), part(p.part)
{
	initializeOpenGLFunctions();

	createBuffer();
}

Particules::Particules(const string id, Mesh *m, const Transform t, const int nbParticules) : Shape3D(id, m, t), n(nbParticules)
{
	init();
}

Particules::~Particules()
{
}

void Particules::draw(QOpenGLShaderProgram *program, const Camera* cam)
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

	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));

	glUseProgram(program->programId());

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glEnableVertexAttribArray(posLocation);
	glVertexAttribPointer(posLocation, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

	glVertexAttribDivisor(vertexLocation, 0); // particles vertices : always reuse the same vertices -> 0
	glVertexAttribDivisor(posLocation, 1); // position : one per particule

	glDrawElementsInstanced(GL_TRIANGLE_FAN, mesh->getIndicesNumber(), GL_UNSIGNED_SHORT, 0, n);

	//reset glVertexAttribDivisor
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);
//	glVertexAttribDivisor(2, 0);

	mesh->release();
}

void Particules::computeAnimation(const float timePass, QOpenGLShaderProgram *compute)
{
	compute->bind();
	compute->setUniformValue("deltaTimeSec", timePass);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, positionBuffer);

	glUseProgram(compute->programId());
	glDispatchCompute((n + 127.0)/128.0, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Particules::init()
{
	initializeOpenGLFunctions();

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> pos(-10, 10);
	uniform_real_distribution<> col(0.5, 1);
	uniform_real_distribution<> speed(1, 3);

	for (int i = 0; i < n; ++i)
	{
		id.push_back(i);
		QVector4D position = QVector4D(pos(gen), pos(gen), pos(gen), 1);
//		QVector4D position = QVector4D(i*2, 0, 0, 1);
//		QVector4D color = QVector4D(col(gen), col(gen), col(gen), 1.0f);
		QVector4D color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
		QVector3D direction = QVector3D(pos(gen), pos(gen), pos(gen));
		direction.normalize();
		part.push_back(Particule{position, color, speed(gen), direction});;
	}

	createBuffer();
}

void Particules::createBuffer()
{
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, n * sizeof(Vec4), NULL, GL_DYNAMIC_DRAW);

	int bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
	Vec4 *pos = (Vec4 *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, n * sizeof(Vec4), bufMask);

	for (int i = 0; i < n; ++i)
	{
		pos[i].x = part[i].position.x();
		pos[i].y = part[i].position.y();
		pos[i].z = part[i].position.z();
		pos[i].w = part[i].position.w();
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
