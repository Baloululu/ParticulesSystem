#include "mesh.h"

Mesh::Mesh() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
	this->init();
}

Mesh::Mesh(vector<VertexData> v, vector<GLushort> i) : indexBuf(QOpenGLBuffer::IndexBuffer)
{
	vertices = v;
	indices = i;
	this->init();
}

void Mesh::init(){
	initializeOpenGLFunctions();
	indexBuf.create();
	arrayBuf.create();
}

Mesh::~Mesh(){
	indexBuf.destroy();
	arrayBuf.destroy();
}

void Mesh::bind(){
	indexBuf.bind();
	arrayBuf.bind();
}

void Mesh::draw(QOpenGLShaderProgram *program)
{
	this->bind();

	quintptr offset = 0;

	int vertexLocation = program->attributeLocation("position");
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	offset += sizeof(QVector3D);

	int colorLocation = program->attributeLocation("color");
	program->enableAttributeArray(colorLocation);
	program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_SHORT, 0);
}

void Mesh::allocate(){
	arrayBuf.bind();
	arrayBuf.allocate(vertices.data(), nbVertices * sizeof(VertexData));

	indexBuf.bind();
	indexBuf.allocate(indices.data(), nbIndices * sizeof(GLushort));
}

int Mesh::getVerticesNumber() const
{
	return nbVertices;
}

int Mesh::getIndicesNumber() const
{
	return nbIndices;
}
