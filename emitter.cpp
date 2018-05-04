#include "emitter.h"
#include <QQuaternion>

Emitter::Emitter()
{

}

QVector3D PointEmitter::getPosition() const
{
	return position;
}

void PointEmitter::setPosition(const QVector3D &value)
{
	position = value;
}

QVector3D PointEmitter::getInitial_velocity() const
{
	return initial_velocity;
}

void PointEmitter::setInitial_velocity(const QVector3D &value)
{
	initial_velocity = value;
}

float PointEmitter::getEmit_angle() const
{
	return emit_angle;
}

void PointEmitter::setEmit_angle(float value)
{
	emit_angle = value;
}

float PointEmitter::getLife() const
{
	return life;
}

void PointEmitter::setLife(float value)
{
	life = value;
}

int PointEmitter::getRate() const
{
	return m_rate;
}

void PointEmitter::setRate(int rate)
{
	m_rate = rate;
}

Particules *PointEmitter::getParticules() const
{
	return particules;
}

void PointEmitter::setParticules(Particules *value)
{
	particules = value;
}

PointEmitter::PointEmitter()
{}

void PointEmitter::emitParticles()
{
	vector<Particule> v = vector<Particule>;
	for (int i = 0; i < m_rate; i++) {
		Particule p = Particule();
		if (this->getEmit_angle() != 0) {
			QQuaternion q = QQuaternion::fromAxisAndAngle(rand_float(-this->getEmit_angle(), this->getEmit_angle()), QVector3D(1.0,0.0,0.0));
			p.setVelocity(q.rotatedVector(p.getVelocity()));
			q = QQuaternion::fromAxisAndAngle(rand_float(-this->getEmit_angle(), this->getEmit_angle()), QVector3D(0.0,1.0,0.0));
			p.setVelocity(q.rotatedVector(p.getVelocity()));
		}
		v.push_back(p);
	}
	this->particules->addParticule(v);
}
