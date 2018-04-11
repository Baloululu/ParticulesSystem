#include "../includes/geometryengine.h"

VertexData vertices[] = {
    {QVector3D(0.0f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(1.0f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f,0.0f)},
    {QVector3D(0.0f, 1.0f, 0.0f), QVector3D(0.0f, 1.0f,0.0f)},
    {QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f,1.0f)},
    {QVector3D(0.0f, 0.0f, 1.0f), QVector3D(0.0f, 0.0f,1.0f)},
};

VertexData vertices2[] = {
    {QVector3D(1.0f, 1.0f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(2.0f, 1.0f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(1.0f, 2.0f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(2.0f, 2.0f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(1.0f, 1.0f, 1.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(2.0f, 1.0f, 1.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(1.0f, 2.0f, 1.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(2.0f, 2.0f, 1.0f), QVector3D(1.0f, 0.0f,0.0f)},
};

const int nbrVertices = 6;

GLushort indices[] = {
    0,1,
    2,3,
    4,5
};

GLushort indices2[] = {
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

const int nbrIndices = 6;


//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer), indexBuf2(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    arrayBuf2.create();
    indexBuf2.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    arrayBuf2.destroy();
    indexBuf2.destroy();
}
//! [0]

void GeometryEngine::initGeometry()
{
////! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices2, 36 * sizeof(GLushort));

    arrayBuf2.bind();
    arrayBuf2.allocate(vertices2, 8 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf2.bind();
    indexBuf2.allocate(indices2, 36 * sizeof(GLushort));
//! [1]
}

//! [2]
void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf2.bind();
    indexBuf2.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    // Tell OpenGL which VBOs to use
//    arrayBuf2.bind();
//    indexBuf2.bind();

    // Draw cube geometry using indices from VBO 1
//    glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_SHORT, 0);
}
//! [2]
