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

#define MIN_LIFE 3
#define MAX_LIFE 4.0f //x.0f important -> flotant envoyé sur le shader
#define RANDOM_ANGLE 10
#define MIN_SPEED 3
#define MAX_SPEED 5

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
	GLuint positionBuffer, directionBuffer, colorBuffer, lifeBuffer, cameBuffer;
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
