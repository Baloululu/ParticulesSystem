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

enum ForceType {
	/** (x,y,z): location; mag1: attraction constant (a = Gm/r^2 = mag1/r^2) */
	ForcePoint,

	/** (x,y,z): direction unit vector; mag1: acceleration
	i.e. for gravity (x,y,z) = (0,0,-1); mag1 = 9.8 */
	ForceDirectional,
};

struct Force{

	QVector3D vect;
	float value;
	ForceType type;
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
