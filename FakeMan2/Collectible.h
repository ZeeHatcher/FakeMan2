#pragma once
#include "CollidableObject.h"
#include "Player.h"
#include "splashkit.h"

class Collectible
	: public CollidableObject
{
public :
	Collectible(float x, float y, int32_t width, int32_t height, color col);
	virtual void collect(Player* player) = 0;
};
