#ifndef EMITTER_H
#define EMITTER_H
#include "mesh/struct.h"
#include "mesh/particules.h"
#include <functional>
#include <memory>

class Emitter
{
public:
	Emitter();
	virtual void emitParticles(std::function<void(Particule)> push_particle) = 0;
};

typedef std::vector<std::unique_ptr<Emitter> > EmitterGroup;

class PointEmitter : public Emitter {
private:
	QVector3D position, initial_velocity;
	Particules* particules;
	float emit_angle, life;
	int m_rate;

public:
	PointEmitter();
	virtual void emitParticles();

	QVector3D getPosition() const;
	void setPosition(const QVector3D &value);
	QVector3D getInitial_velocity() const;
	void setInitial_velocity(const QVector3D &value);
	float getEmit_angle() const;
	void setEmit_angle(float value);
	float getLife() const;
	void setLife(float value);
	int getRate() const;
	void setRate(int rate);
	Particules *getParticules() const;
	void setParticules(Particules *value);
};

#endif // EMITTER_H
