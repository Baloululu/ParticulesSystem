#include "particule.h"

Particule::Particule() : pos(0, 0, 0, 0), dir(0, 0, 0, 0), col(1, 1, 1, 1), li(0), camDist(-1)
{
}

Particule::Particule(QVector4D position, QVector4D direction, QVector4D color, float life, float cameradistance) : pos(position), dir(direction), col(color), li(life), camDist(cameradistance)
{
}

void Particule::setVector(const ParticuleAttribute attrib, const QVector4D vec)
{
	switch (attrib) {
	case position:
		pos = vec;
		break;
	case direction:
		dir = vec;
		break;
	case color:
		col = vec;
		break;
	}
}

void Particule::setFloat(const ParticuleAttribute attrib, const float nb)
{
	switch (attrib) {
	case life:
		li = nb;
		break;
	case cameraDist:
		camDist = nb;
		break;
	}
}

QVector4D Particule::getVector(const ParticuleAttribute attrib) const
{
	switch (attrib) {
	case position:
		return this->pos;
		break;
	case direction:
		return this->dir;
		break;
	case color:
		return this->col;
		break;
	default:
		return QVector4D(0, 0, 0, 0);
		break;
	}
}

float Particule::getFloat(const ParticuleAttribute attrib) const
{
	switch (attrib) {
	case life:
		return this->li;
		break;
	case cameraDist:
		return this->camDist;
		break;
	default:
		return 0;
		break;
	}
}

bool Particule::operator <(const Particule &p2) const
{
	return camDist > p2.camDist;
}
