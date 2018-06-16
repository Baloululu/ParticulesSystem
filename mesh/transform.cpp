#include "transform.h"

Transform::Transform() : position(0, 0, 0), scale(1, 1, 1), rotation()
{
	rotation = QQuaternion::fromAxisAndAngle(0, 0, 1, 0);
}

Transform::Transform(const Transform& t) : position(t.position), scale(t.scale), rotation(t.rotation)
{
}

Transform::Transform(QVector3D p, QVector3D s, QQuaternion q) : position(p), scale(s), rotation(q)
{
}

Transform::~Transform()
{
}

QVector3D Transform::getPosition() const
{
	return position;
}

QVector3D Transform::getScale() const
{
	return scale;
}

QQuaternion Transform::getRotation() const
{
	return rotation;
}

QMatrix4x4 Transform::getCompute()
{
	QMatrix4x4 mat;

	mat.setToIdentity();

	rotation.normalize();

	mat.scale(scale);
	mat.rotate(rotation);
	mat.translate(position);

	return mat;
}

void Transform::setPosition(const QVector3D p){
	position = p;
}

void Transform::setScale(const QVector3D s){
	scale = s;
}

void Transform::setRotation(const QQuaternion q){
	rotation = q;
}
