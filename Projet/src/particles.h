#ifndef PARTICLES_H
#define PARTICLES_H

#include <QVector3D>

class Particule {

private:
    QVector3D pos, velocity;
    float age, life;

public:
    Particule();
    Particule(QVector3D pos, QVector3D v, float life);
    const QVector3D &getPos() const;
    void setPos(const QVector3D &pos);
    const QVector3D &getVelocity() const;
    void setVelocity(const QVector3D &velocity);
    float getAge() const;
    void setAge(float age);
    float getLife() const;

};
    std::ostream& operator<<(std::ostream& stream, Particule const& p);
#endif // PARTICLES_H
