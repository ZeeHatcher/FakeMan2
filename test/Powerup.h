#pragma once
#include "Collectible.h"
#include "Dimensions.h"
#include "splashkit.h"

class Powerup :
    public Collectible
{
public:
	Powerup(float x, float y);
	void collect(Player* player);
	void draw();
};

