#include "cube.h"

Cube::Cube() : Mesh()
{
	nbVertices = 8;
	nbIndices = 36;

	vertices.push_back(VertexData {QVector3D(-1.0f, -1.0f, 1.0f), QVector4D(1.0f, 0.0f, 0.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(1.0f, -1.0f, 1.0f), QVector4D(0.0f, 1.0f, 0.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(-1.0f, 1.0f, 1.0f), QVector4D(0.0f, 0.0f, 1.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(1.0f, 1.0f, 1.0f), QVector4D(1.0f, 1.0f, 1.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(-1.0f, -1.0f, -1.0f), QVector4D(1.0f, 1.0f, 1.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(1.0f, -1.0f, -1.0f), QVector4D(1.0f, 0.0f, 0.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(-1.0f, 1.0f, -1.0f), QVector4D(0.0f, 1.0f, 0.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(1.0f, 1.0f, -1.0f), QVector4D(0.0f, 0.0f, 1.0f, 1.0f)} );

	indices.push_back(2); indices.push_back(7); indices.push_back(6);
	indices.push_back(2); indices.push_back(3); indices.push_back(7);
	indices.push_back(0); indices.push_back(3); indices.push_back(2);
	indices.push_back(1); indices.push_back(3); indices.push_back(0);
	indices.push_back(1); indices.push_back(7); indices.push_back(3);
	indices.push_back(5); indices.push_back(7); indices.push_back(1);
	indices.push_back(6); indices.push_back(7); indices.push_back(5);
	indices.push_back(4); indices.push_back(6); indices.push_back(5);
	indices.push_back(2); indices.push_back(6); indices.push_back(4);
	indices.push_back(0); indices.push_back(2); indices.push_back(4);
	indices.push_back(0); indices.push_back(4); indices.push_back(5);
	indices.push_back(1); indices.push_back(0); indices.push_back(5);

	allocate();
}

Cube::~Cube()
{
}
