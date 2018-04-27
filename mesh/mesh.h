#ifndef MESH_H
#define MESH_H

#include "struct.h"
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class Mesh : protected QOpenGLFunctions
{
public:
	Mesh();
	Mesh(VertexData *v, GLushort *i);
	~Mesh();
	void bind();

	int getVerticesNumber() const;
	int getIndicesNumber() const;

protected:
	void allocate();

	VertexData *vertices;
	int nbVertices;
	GLushort *indices;
	int nbIndices;

	QOpenGLBuffer arrayBuf;
	QOpenGLBuffer indexBuf;

private:
	void init();
};

#endif // MESH_H
