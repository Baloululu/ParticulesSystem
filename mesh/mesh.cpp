#include "mesh.h"

Mesh::Mesh() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
	this->init();
	qDebug() << "MeshInit";
}

Mesh::Mesh(vector<VertexData> v, vector<GLushort> i) : indexBuf(QOpenGLBuffer::IndexBuffer)
{
	vertices = v;
	indices = i;
	this->init();
}

Mesh::~Mesh()
{
	indexBuf.destroy();
	arrayBuf.destroy();
}

void Mesh::init(){
	initializeOpenGLFunctions();
	indexBuf.create();
	arrayBuf.create();
}

void Mesh::bind(){
	indexBuf.bind();
	arrayBuf.bind();
}

void Mesh::release()
{
	indexBuf.release();
	arrayBuf.release();
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

	this->release();
}

void Mesh::allocate(){
	this->bind();
	arrayBuf.allocate(vertices.data(), nbVertices * sizeof(VertexData));
	indexBuf.allocate(indices.data(), nbIndices * sizeof(GLushort));
	this->release();
}

int Mesh::getVerticesNumber() const
{
	return nbVertices;
}

int Mesh::getIndicesNumber() const
{
	return nbIndices;
}
