#include "../../includes/mesh/mesh.h"

Mesh::Mesh() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    vertices = {};
    indices = {};
    this->init();
}

Mesh::Mesh(VertexData *v, GLushort *i) : indexBuf(QOpenGLBuffer::IndexBuffer)
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

void Mesh::allocate(){
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbVertices * sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, nbIndices * sizeof(GLushort));
}

int Mesh::getVerticesNumber() const
{
    return nbVertices;
}

int Mesh::getIndicesNumber() const
{
    return nbIndices;
}
