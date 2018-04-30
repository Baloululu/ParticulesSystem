#ifndef PARTICULES_H
#define PARTICULES_H

#include "shape3d.h"
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <vector>
#include <random>
#include "shape3d.h"
#include "billboard.h"
#include "struct.h"
#include <algorithm>
#include "deepsorter.h"

#include <QDebug>

using namespace std;

class Particules : public Shape3D, protected QOpenGLExtraFunctions
{
public:
	Particules();
	Particules(const Particules& p);
	Particules(const string id, Mesh *m, const Transform t, const int nbParticules);
	~Particules();

	void draw(QOpenGLShaderProgram *program, const Camera* cam);
	virtual void computeAnimation(const float timePass);

private:

	void init();

	int n;
	vector<Particule> part;
	QOpenGLBuffer posBuff;
	void createBuffer();
	bool sortParticule(Particule a, Particule b);
};

#endif // PARTICULES_H
