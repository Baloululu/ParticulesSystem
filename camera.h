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
	void loockAt(QVector3D pos);

	void calculateProjection(int w, int h);
	QMatrix4x4 cameraMatrix() const;

	void setSpeed(const float v);
	float getSpeed() const;

	QVector3D getUp() const;
	QVector3D getDir() const;

	QVector3D getPosition() const;

private:
	QVector3D position, direction;
	QVector3D up;
	QMatrix4x4 projection;
	float speed;
};

#endif // CAMERA_H
