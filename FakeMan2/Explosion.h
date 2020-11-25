#pragma once
#include "CollidableObject.h"
#include "Dimensions.h"
#include "splashkit.h"

class Explosion
	: public CollidableObject
{
public :
	Explosion(float x, float y, bool isDraw);
	bool canDissipate();
	void decrementActualTimeToDissipate();
	void draw();

private :
	int actualTimeToDissipate_;
	bool isDraw_;
};
