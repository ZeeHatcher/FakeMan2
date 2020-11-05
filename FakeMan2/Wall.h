#pragma once
#include "CollidableObject.h"
#include "Dimensions.h"
#include "splashkit.h"

class Wall
	: public CollidableObject
{
public :
	Wall(float x, float y);
	Wall(float x, float y, color clr);
	void draw();
};
