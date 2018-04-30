#include "deepsorter.h"

DeepSorter::DeepSorter(Camera* camera) : cam(camera)
{
}

bool DeepSorter::operator()(Particule& a, Particule& b) const
{
	cam->getPosition().distanceToPoint(a.position) < cam->getPosition().distanceToPoint(b.position);
}
