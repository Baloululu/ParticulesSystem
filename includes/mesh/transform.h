#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform
{
public:
    Transform();
    Transform(const Transform& t);
    Transform(QVector3D p, QVector3D s, QQuaternion q);
    ~Transform();

    QVector3D getPosition() const;
    QVector3D getScale() const;
    QQuaternion getRotation() const;

    QMatrix4x4 getCompute();

    void setPosition(const QVector3D p);
    void setScale(const QVector3D s);
    void setRotation(const QQuaternion q);

private:
    QVector3D position, scale;
    QQuaternion rotation;
};

#endif // TRANSFORM_H
