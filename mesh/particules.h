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
	virtual void computeAnimation(const float timePass, QOpenGLShaderProgram *compute);

private:

	void init();

	int n;
	vector<Particule> part;
	vector<int> id;
	GLuint positionBuffer, directionBuffer, colorBuffer;
	void createBuffer();
};

#endif // PARTICULES_H
