#ifndef MESH_H
#define MESH_H

#include "struct.h"
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <vector>

using namespace std;

class Mesh : protected QOpenGLFunctions
{
public:
	Mesh();
	Mesh(vector<VertexData> v, vector<GLushort> i);
	~Mesh();
	void bind();

	virtual void draw(QOpenGLShaderProgram *program);

	int getVerticesNumber() const;
	int getIndicesNumber() const;

protected:
	void allocate();

	vector<VertexData> vertices;
	int nbVertices;
	vector<GLushort> indices;
	int nbIndices;

	QOpenGLBuffer arrayBuf;
	QOpenGLBuffer indexBuf;

private:
	void init();
};

#endif // MESH_H
