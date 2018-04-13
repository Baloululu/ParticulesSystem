#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Camera
{
public:
	Camera();
	Camera(QVector3D pos, QVector3D dir);

	void moveTo(QVector3D vect);
	void moveTo(float x, float y, float z);
	void move(QVector3D vect);
	void move(float x, float y, float z);
	void rotate(QQuaternion q);

	void calculateProjection(int w, int h);
	QMatrix4x4 cameraMatrix() const;

private:
	QVector3D position, direction;
	const QVector3D cameraUp;
	QMatrix4x4 projection;
};

#endif // CAMERA_H
