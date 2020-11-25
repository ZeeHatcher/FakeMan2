#pragma once
#include <cmath>
#include <vector>
#include "Cell.h"
#include "Dimensions.h"
#include "DrawableObject.h"
#include "Explosion.h"
#include "splashkit.h"
#include "Wall.h"

class Bomb
	: public DrawableObject
{
public :
	Bomb(float x, float y);
	bool canExplode();
	void decrementActualTimeToExplode();
	void draw();
	void explode(std::vector<std::vector<Cell*>>& cells, std::vector<Wall*>& walls, std::vector<Explosion*>& explosions);

private :
	int actualTimeToExplode_;
	int explosionRadius_;
};
