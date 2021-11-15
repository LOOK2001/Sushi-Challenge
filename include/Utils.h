#ifndef UTILS_H
#define UTILS_H

#include "GameObject.h"


static float Distance(SDL_FPoint p1, SDL_FPoint p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

#endif //UTILS_H