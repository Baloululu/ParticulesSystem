#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "mesh.h"
#include <math.h>

class Billboard : public Mesh
{
public:
	Billboard();
	Billboard(const int n);
	Billboard(const int n, const float size);
	Billboard(const int n, const float, const QVector4D color);
	~Billboard();

	virtual void draw(QOpenGLShaderProgram *program);

private:
	void generateMesh(const int n, const float size, const QVector4D color);
};

#endif // BILLBOARD_H
