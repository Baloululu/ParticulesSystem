#include "billboard.h"

Billboard::Billboard()
{
	generateMesh(4, 1, QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
}

Billboard::Billboard(const int n)
{
	generateMesh(n, 1, QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
}

Billboard::Billboard(const int n, const float size)
{
	generateMesh(n, size, QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
}

Billboard::Billboard(const int n, const float size, const QVector4D color)
{
	generateMesh(n, size, color);
}

Billboard::~Billboard()
{
}

void Billboard::draw(QOpenGLShaderProgram *program)
{
	this->bind();

	quintptr offset = 0;

	int vertexLocation = program->attributeLocation("position");
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	offset += sizeof(QVector3D);

	int colorLocation = program->attributeLocation("color");
	program->enableAttributeArray(colorLocation);
	program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

	glDrawElements(GL_TRIANGLE_FAN, nbIndices, GL_UNSIGNED_SHORT, 0);

	this->release();
}

void Billboard::generateMesh(const int n, const float size, const QVector4D color)
{
	nbVertices = n;
	nbIndices = n;

	float offset = 0, step = (2 * M_PI) / (float) n;

	if (n % 2 == 0)
		offset = step / 2.0;

	int i;

	for(i = 0; i < n; ++i)
	{
		float angle = (step * i) + offset;
		vertices.push_back(VertexData {QVector3D(cos(angle) * size, sin(angle) * size, 0.0f), color} );
		indices.push_back(i);
	}

	allocate();
}
