#ifndef STRUCT_H
#define STRUCT_H

#include <QVector3D>
#include <QVector4D>

struct VertexData
{
	QVector3D position;
	QVector4D color;
};

struct Particule
{
	QVector3D position;
	QVector4D color;
	float speed;
	QVector3D direction;
};

struct ParticuleCompare
{
	ParticuleCompare(QVector3D camPosition) { this->camera = camPosition; }
	bool operator () (Particule a, Particule b) {
		return camera.distanceToPoint(a.position) > camera.distanceToPoint(b.position);
	}

	QVector3D camera;
};

#endif // STRUCT_H
