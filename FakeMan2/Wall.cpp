#include "Wall.h"

Wall::Wall(float x, float y)
	: Wall(x, y, ColorGray)
{
}

Wall::Wall(float x, float y, color clr)
	: CollidableObject(x, y, TILE_DIM, TILE_DIM, clr)
{
}

void Wall::draw()
{
	draw_rectangle(color_, bounding_);
}