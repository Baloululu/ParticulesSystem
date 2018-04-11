#include "../../includes/mesh/shape3d.h"

Shape3D::Shape3D() : transform(), mesh(), name()
{
}

Shape3D::Shape3D(const Shape3D& s) : transform(s.transform), name(s.name)
{
    this->mesh = s.mesh;
}

Shape3D::Shape3D(char *name, Mesh *m, Transform t) : transform(t), name(name), mesh(m)
{
}

Shape3D::~Shape3D()
{
}

void Shape3D::setPosition(const QVector3D p)
{
    transform.setPosition(p);
}

void Shape3D::setScale(const QVector3D s)
{
    transform.setScale(s);
}

void Shape3D::setRotation(const QQuaternion q)
{
    transform.setRotation(q);
}

void Shape3D::setTransform(const Transform t)
{
    transform = t;
}

void Shape3D::setMesh(Mesh* m)
{
    mesh = m;
}

QVector3D Shape3D::getPosition() const
{
    return transform.getPosition();
}

QVector3D Shape3D::getScale() const
{
    return transform.getScale();
}

QQuaternion Shape3D::getRotation() const
{
    return transform.getRotation();
}

Transform Shape3D::getTransform() const
{
    return transform;
}

Mesh* Shape3D::getMesh() const
{
    return mesh;
}

void Shape3D::draw(QOpenGLShaderProgram *program)
{
    mesh->bind();

    program->setUniformValue("transform", transform.getCompute());

    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    glDrawElements(GL_TRIANGLES, mesh->getIndicesNumber(), GL_UNSIGNED_SHORT, 0);
}
