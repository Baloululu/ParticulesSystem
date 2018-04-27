#include "camera.h"

Camera::Camera() : position(0,0,0), direction(0,0,1), projection(), up(0,1,0), speed(1)
{
}

Camera::Camera(QVector3D pos, QVector3D dir) : position(pos), direction(dir), projection(), up(0,1,0), speed(1)
{
}

void Camera::moveTo(QVector3D vect)
{
	position = vect;
}

void Camera::moveTo(float x, float y, float z)
{
	position.setX(x);
	position.setY(y);
	position.setZ(z);
}

void Camera::move(QVector3D vect)
{
	position += vect;
}

void Camera::move(float x, float y, float z)
{
	position.setX(position.x() + x);
	position.setY(position.y() + y);
	position.setZ(position.z() + z);
}

void Camera::rotate(QQuaternion q)
{
	q.normalize();
	direction = q.rotatedVector(direction);
	up = q.rotatedVector(up);
}

void Camera::calculateProjection(int w, int h)
{
	qreal aspect = qreal(w) / qreal(h ? h : 1);

	const qreal zNear = 1.0, zFar = 50.0, fov = 45.0;

	projection.setToIdentity();

	projection.perspective(fov, aspect, zNear, zFar);
}

QMatrix4x4 Camera::cameraMatrix() const
{
	QMatrix4x4 view;
	view.setToIdentity();
	view.lookAt(position, position + direction, up);

	return projection * view;
}

void Camera::setSpeed(const float v)
{
	if (v < 0)
		speed = 0;
	else
		speed = v;
}

float Camera::getSpeed() const
{
	return speed;
}

QVector3D Camera::getUp() const
{
	return up;
}

QVector3D Camera::getDir() const
{
	return direction;
}
