#include "../../includes/mesh/cube.h"

Cube::Cube() : Mesh()
{
	nbVertices = 8;
	nbIndices = 36;

	VertexData verticesTemp[] = {
		{QVector3D(-1.0f, -1.0f, 1.0f), QVector3D(1.0f, 1.0f,1.0f)},
		{QVector3D(1.0f, -1.0f, 1.0f), QVector3D(1.0f, 1.0f,1.0f)},
		{QVector3D(-1.0f, 1.0f, 1.0f), QVector3D(1.0f, 1.0f,1.0f)},
		{QVector3D(1.0f, 1.0f, 1.0f), QVector3D(1.0f, 1.0f,1.0f)},
		{QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(1.0f, 1.0f,1.0f)},
		{QVector3D(1.0f, -1.0f, -1.0f), QVector3D(1.0f, 1.0f,1.0f)},
		{QVector3D(-1.0f, 1.0f, -1.0f), QVector3D(1.0f, 1.0f,1.0f)},
		{QVector3D(1.0f, 1.0f, -1.0f), QVector3D(1.0f, 1.0f,1.0f)}
	};

	GLushort indicesTemp[] = {
		2,7,6,
		2,3,7,
		0,3,2,
		1,3,0,
		1,7,3,
		5,7,1,
		6,7,5,
		4,6,5,
		2,6,4,
		0,2,4,
		0,4,5,
		1,0,5
	};

	indices = indicesTemp;
	vertices = verticesTemp;

	allocate();
}

Cube::~Cube(){
}
