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
	posBuff.destroy();
}

void Particules::addParticule(Particule &p)
{
	this->part.push_back(p);
}

void Particules::addParticule(vector<Particule> &v)
{
	this->part.insert(part.end(), v.begin(), v.end());
}

void Particules::draw(QOpenGLShaderProgram *program, const Camera* cam)
{
	sort(part.begin(), part.end(), ParticuleCompare(cam->getPosition()));

	posBuff.bind();
	auto ptr = posBuff.map(QOpenGLBuffer::WriteOnly);
	memcpy(ptr, part.data(), part.size() * sizeof(Particule));
	posBuff.unmap();
	posBuff.release();

	program->setUniformValue("transform", transform.getCompute());

	mesh->bind();

	int vertexLocation = program->attributeLocation("position");
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));

	posBuff.bind();

	quintptr offset = 0;

	int location = program->attributeLocation("loc");
	program->enableAttributeArray(location);
	program->setAttributeBuffer(location, GL_FLOAT, 0, 3, sizeof(Particule));

	offset += sizeof(QVector3D);

	int colorLocation = program->attributeLocation("color");
	program->enableAttributeArray(colorLocation);
	program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 4, sizeof(Particule));

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same vertices -> 0
	glVertexAttribDivisor(1, 1); // color : one per quad -> 1 but here 0 for all same color
	glVertexAttribDivisor(2, 1); // positions : one per quad (its center) -> 1

	glDrawElementsInstanced(GL_TRIANGLE_FAN, mesh->getIndicesNumber(), GL_UNSIGNED_SHORT, 0, n);

	//reset glVertexAttribDivisor
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);
	glVertexAttribDivisor(2, 0);

	mesh->release();
	posBuff.release();
}

void Particules::computeAnimation(const float timePass)
{
	for (vector<Particule>::iterator it = part.begin(); it != part.end(); ++it)
	{
		QVector3D temp = it->position + it->direction * it->speed * timePass;

		if (temp.x() < -10 || temp.x() > 10)
			it->direction.setX(-it->direction.x());

		if (temp.y() < -10 || temp.y() > 10)
			it->direction.setY(-it->direction.y());

		if (temp.z() < -10 || temp.z() > 10)
			it->direction.setZ(-it->direction.z());

		it->position += it->direction * it->speed * timePass;
	}
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
		QVector3D position = QVector3D(pos(gen), pos(gen), pos(gen));
		QVector4D color = QVector4D(col(gen), col(gen), col(gen), 1.0f);
		QVector3D direction = QVector3D(pos(gen), pos(gen), pos(gen));
		direction.normalize();
		part.push_back(Particule{position, color, speed(gen), direction});
	}

	createBuffer();
}

void Particules::createBuffer()
{
	posBuff.create();
	posBuff.bind();
	posBuff.setUsagePattern(QOpenGLBuffer::DynamicDraw);
	posBuff.allocate(part.data(), n * sizeof(Particule));
	posBuff.release();
}
