#ifndef PARTICULE_H
#define PARTICULE_H

#include <QVector4D>
#include "struct.h"

class Particule
{
public:
	Particule();
	Particule(QVector4D position, QVector4D direction, QVector4D color, float life, float cameradistance);
	QVector4D getVector(const ParticuleAttribute attrib) const;
	float getFloat(const ParticuleAttribute attrib) const;

	void setVector(const ParticuleAttribute attrib, const QVector4D vec);
	void setFloat(const ParticuleAttribute attrib, const float nb);

	bool operator <(const Particule& p2) const;

private:
	QVector4D pos, dir, col;
	float li, camDist;
};

#endif // PARTICULE_H
