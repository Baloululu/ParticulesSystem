#ifndef PARTICULES_H
#define PARTICULES_H

#include "shape3d.h"
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <vector>
#include <random>
#include "shape3d.h"
#include "billboard.h"

#include <QDebug>

using namespace std;

class Particules : public Shape3D, protected QOpenGLExtraFunctions
{
public:
	Particules();
	Particules(const string id, Mesh *m, const Transform t, const int nbParticules);
	~Particules();

	virtual void draw(QOpenGLShaderProgram *program);

private:

	void init();

	int n;
	vector<QVector3D> positions;
	QOpenGLBuffer posBuff;
};

#endif // PARTICULES_H
