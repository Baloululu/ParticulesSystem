#ifndef DEEPSORTER_H
#define DEEPSORTER_H

#include "camera.h"
#include "particules.h"

class DeepSorter
{
public:
	DeepSorter(Camera* camera);
	bool operator() (Particule& a, Particule& b) const;

private:
	Camera* cam;
};

#endif // DEEPSORTER_H
