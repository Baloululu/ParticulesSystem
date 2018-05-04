#include "force.h"

Force::Force()
{
    this->setVect(QVector3D(0.0,0.0,0.0));
    this->setType(ForcePoint);
    this->setValue(1.0);
}

Force::Force(QVector3D vect, float value, ForceType type){
    this->vect=vect;
    this->value=value;
    this->type=type;
}

QVector3D Force::getVect() const
{
    return vect;
}

void Force::setVect(const QVector3D &value)
{
    vect = value;
}

float Force::getValue() const
{
    return value;
}

void Force::setValue(float value)
{
    value = value;
}

ForceType Force::getType() const
{
    return type;
}

void Force::setType(const ForceType &value)
{
    type = value;
}

std::ostream& operator<<(std::ostream& stream, Force const& f)
{
    stream << "Vect : (" <<f.getVect().x() << "," << f.getVect().y() << "," << f.getVect().z() << ")" <<std::endl;
    stream << "Value " << f.getValue() << std::endl;
    stream << "ForceType : " << f.getType() << std::endl;
    return stream;
}
