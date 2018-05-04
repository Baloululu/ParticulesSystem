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

PointEmitter::PointEmitter()
{}

void PointEmitter::emitParticles(std::function<void(Particule)> push_particle)
{
    for (int i = 0; i < m_rate; i++) {
        Particule p = Particule();
        if (this->getEmit_angle() != 0) {
            QQuaternion q = QQuaternion(rand_float(-this->getEmit_angle(), this->getEmit_angle()), QVector3D(1.0,0.0,0.0));
            p.setVelocity(q.rotatedVector(p.getVelocity()));
            q = QQuaternion(rand_float(-this->getEmit_angle(), this->getEmit_angle()), QVector3D(0.0,1.0,0.0));
            p.setVelocity(q.rotatedVector(p.getVelocity()));
        }
        push_particle(p);
    }
}
