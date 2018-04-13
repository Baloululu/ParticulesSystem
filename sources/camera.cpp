#include "../includes/camera.h"

Camera::Camera() : position(0,0,0), direction(0,0,1), projection(), cameraUp(0,1,0)
{
}

Camera::Camera(QVector3D pos, QVector3D dir) : position(pos), direction(dir), projection(), cameraUp(0,1,0)
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
	direction = q.rotatedVector(direction);
}

void Camera::calculateProjection(int w, int h)
{
	qreal aspect = qreal(w) / qreal(h ? h : 1);

	const qreal zNear = 2.0, zFar = 10.0, fov = 100.0;

	projection.setToIdentity();

	projection.perspective(fov, aspect, zNear, zFar);
}

QMatrix4x4 Camera::cameraMatrix() const
{
	QMatrix4x4 view;
	view.setToIdentity();
	view.lookAt(position, position + direction, cameraUp);

	return projection * view;
}
