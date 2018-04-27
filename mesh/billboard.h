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
	~Billboard();

	virtual void draw(QOpenGLShaderProgram *program);

private:
	void generateMesh(const int n, const float size);
};

#endif // BILLBOARD_H
