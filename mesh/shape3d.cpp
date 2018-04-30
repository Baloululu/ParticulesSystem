#include "shape3d.h"

Shape3D::Shape3D() : transform(), mesh(), name()
{
}

Shape3D::Shape3D(const string n, Mesh *m, const Transform t) : transform(t), name(n), mesh(m)
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
	program->setUniformValue("transform", transform.getCompute());

	mesh->draw(program);
}

void Shape3D::computeAnimation(const float timePass)
{
}
