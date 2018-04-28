#include "particules.h"

Particules::Particules() : Shape3D(), n(10)
{
}

Particules::Particules(const string id, Mesh *m, const Transform t, const int nbParticules) : Shape3D(id, m, t), n(nbParticules)
{
	init();
}

Particules::~Particules()
{
}

void Particules::draw(QOpenGLShaderProgram *program)
{
	program->setUniformValue("transform", transform.getCompute());

	mesh->bind();

	quintptr offset = 0;

	int vertexLocation = program->attributeLocation("position");
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	offset += sizeof(QVector3D);

	int colorLocation = program->attributeLocation("color");
	program->enableAttributeArray(colorLocation);
	program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	posBuff.bind();

	int location = program->attributeLocation("loc");
	program->enableAttributeArray(location);
	program->setAttributeBuffer(location, GL_FLOAT, 0, 3, sizeof(QVector3D));

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same vertices -> 0
	glVertexAttribDivisor(1, 0); // color : one per quad -> 1 but here 0 for all same color
	glVertexAttribDivisor(2, 1); // positions : one per quad (its center) -> 1

	glDrawElementsInstanced(GL_TRIANGLE_FAN, mesh->getIndicesNumber(), GL_UNSIGNED_SHORT, 0, n);

	mesh->release();
	posBuff.release();
}

void Particules::init()
{
	initializeOpenGLFunctions();

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> pos(-10, 10);

	for (int i = 0; i < n; ++i)
	{
		positions.push_back(QVector3D(pos(gen), pos(gen), pos(gen)));
	}

	posBuff.create();
	posBuff.bind();
	posBuff.allocate(positions.data(), n * sizeof(QVector3D));
	posBuff.release();
}
