#ifndef FORCE_H
#define FORCE_H

#include <iostream>
#include <QVector3D>

enum ForceType {
    /** (x,y,z): location; mag1: attraction constant (a = Gm/r^2 = mag1/r^2) */
    ForcePoint,

    /** (x,y,z): direction unit vector; mag1: acceleration
    i.e. for gravity (x,y,z) = (0,0,-1); mag1 = 9.8 */
    ForceDirectional,
};

inline std::ostream& operator<<(std::ostream & stream, const ForceType& type){
    switch(type){
    case ForcePoint:
      stream << "ForcePoint" << std::endl;
      break;
    case ForceDirectional:
      stream << "ForceDirectional" << std::endl;
      break;
    default:
      break;
  }
  return stream;
}

class Force
{

private:

    QVector3D vect;
    float value;
    ForceType type;

public:

    Force();
    Force(QVector3D vect, float value, ForceType type);
    QVector3D getVect() const;
    void setVect(const QVector3D &value);
    float getValue() const;
    void setValue(float value);
    ForceType getType() const;
    void setType(const ForceType &value);
};

#endif // FORCE_H
