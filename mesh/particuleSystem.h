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
#include "particule.h"
#include <algorithm>
#include <math.h>

#include <QDebug>

#define NB_PARTICULES_EMIT 1000.0

using namespace std;

class ParticuleSystem : public Shape3D, protected QOpenGLExtraFunctions
{
public:
	ParticuleSystem();
	ParticuleSystem(const ParticuleSystem& p);
	ParticuleSystem(const string id, Mesh *m, const Transform t, const int nbParticules);
	~ParticuleSystem();

	void draw(QOpenGLShaderProgram *program, const Camera* cam);
	virtual void computeAnimation(const float timePass, QOpenGLShaderProgram *compute, const QVector4D cameraPosition);

private:

	void init();

	int n, nbActivePart;
	vector<Particule> part;
	vector<int> id;
	GLuint positionBuffer, directionBuffer, colorBuffer, speedBuffer, lifeBuffer, cameBuffer;
	void createBuffer();

	void emitParticules(const float timePass);
	void physiqueCalculating(const float timePass, QOpenGLShaderProgram *compute, const QVector4D cameraPosition);
	void sort();
	void readBuffer();
	void writeBuffer();

	void fillVec4Buffer(GLuint *buffer, ParticuleAttribute attrib);
	void fillFloatBuffer(GLuint *buffer, ParticuleAttribute attrib);

	void readFloatBuffer(GLuint *buffer, ParticuleAttribute attrib);
	void readVec4Buffer(GLuint *buffer, ParticuleAttribute attrib);
};

#endif // PARTICULES_H
