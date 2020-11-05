#pragma once
#include "CollidableObject.h"
#include "Dimensions.h"
#include "SwinGame.h"

class Explosion
	: public CollidableObject
{
public :
	Explosion(float x, float y);
	bool canDissipate();
	void decrementActualTimeToDissipate();
	void draw();

private :
	int actualTimeToDissipate_;
};
