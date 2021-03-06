#ifndef STRUCT_H
#define STRUCT_H

#include <QVector3D>
#include <QVector4D>

struct VertexData
{
	QVector3D position;
	QVector4D color;
};

//struct Particule
//{
//	QVector4D position;
//	QVector4D color;
//	QVector4D direction;
//	float speed, life;
//};

enum ParticuleAttribute
{
	position, direction, color, life, cameraDist
};

struct Vec4
{
	float x, y, z, w;
};

//struct ParticuleCompare
//{
//	ParticuleCompare(QVector3D camPosition) { this->camera = camPosition; }
//	bool operator () (Particule a, Particule b) {
//		return camera.distanceToPoint(a.position.toVector3D()) > camera.distanceToPoint(b.position.toVector3D());
//	}

//	QVector3D camera;
//};

#endif // STRUCT_H
