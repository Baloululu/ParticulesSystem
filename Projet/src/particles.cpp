//
// Created by pierr on 26/04/2018.
//
#include <iostream>
#include "particles.h"

Particule::Particule(QVector3D pos, QVector3D v, float life){
    this->pos=pos;
    this->velocity = velocity;
    this->life=life;
    this->age=0.0;
}

Particule::Particule(){
    this->pos= QVector3D(0.0,0.0,0.0);
    this->velocity = QVector3D(0.0,0.0,0.0);
    this->age=0.0;
    this->life=1.0;
}

const QVector3D &Particule::getPos() const {
    return pos;
}

void Particule::setPos(const QVector3D &pos) {
    Particule::pos = pos;
}

const QVector3D &Particule::getVelocity() const {
    return velocity;
}

void Particule::setVelocity(const QVector3D &velocity) {
    Particule::velocity = velocity;
}

float Particule::getAge() const {
    return age;
}

void Particule::setAge(float age) {
    Particule::age = age;
}

float Particule::getLife() const {
    return life;
}

std::ostream& operator<<(std::ostream& stream, Particule const& p)
{
    stream << "Position : (" <<p.getPos().x() << "," << p.getPos().y() << "," << p.getPos().z() << ")" <<std::endl;
    stream << "Velocity : (" <<p.getVelocity().x() << "," << p.getVelocity().y() << "," << p.getVelocity().z() << ")" <<std::endl;
    stream << "Age : " << p.getAge() << std::endl;
    stream << "Vie : " << p.getLife() << std::endl;
    return stream;
}
