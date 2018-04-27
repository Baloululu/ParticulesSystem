#ifndef SHAPE3D_H
#define SHAPE3D_H

#include "transform.h"
#include "mesh.h"
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QQuaternion>
#include <QDebug>

#include <string>

using namespace std;

class Shape3D
{
public:
	Shape3D();
	Shape3D(const Shape3D& s);
	Shape3D(const string n, Mesh *m, const Transform t);
	~Shape3D();

	void draw(QOpenGLShaderProgram *program);

	void setPosition(const QVector3D p);
	void setScale(const QVector3D s);
	void setRotation(const QQuaternion q);
	void setTransform(const Transform t);
	void setMesh(Mesh* m);

	QVector3D getPosition() const;
	QVector3D getScale() const;
	QQuaternion getRotation() const;
	Transform getTransform() const;
	Mesh* getMesh() const;

private:
	Transform transform;
	Mesh* mesh;
	string name;
};

#endif // SHAPE3D_H
