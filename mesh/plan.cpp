#include "plan.h"

Plan::Plan() : Mesh()
{
	nbVertices = 4;
	nbIndices = 6;

	vertices.push_back(VertexData {QVector3D(-1.0f, -1.0f, 0.0f), QVector4D(0.0f, 0.0f, 0.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(1.0f, -1.0f, 0.0f), QVector4D(0.0f, 0.0f, 0.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(-1.0f, 1.0f, 0.0f), QVector4D(0.0f, 0.0f, 0.0f, 1.0f)} );
	vertices.push_back(VertexData {QVector3D(1.0f, 1.0f, 0.0f), QVector4D(0.0f, 0.0f, 0.0f, 1.0f)} );

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(3); indices.push_back(2); indices.push_back(1);

	allocate();
}

Plan::~Plan()
{
}
