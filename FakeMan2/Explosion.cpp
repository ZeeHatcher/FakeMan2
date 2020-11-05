#include "Explosion.h"

Explosion::Explosion(float x, float y)
	: CollidableObject(x, y, TILE_DIM, TILE_DIM, ColorOrange)
{
	actualTimeToDissipate_ = 10;
}

bool Explosion::canDissipate()
{
	return (actualTimeToDissipate_ == 0);
}

void Explosion::decrementActualTimeToDissipate()
{
	actualTimeToDissipate_--;
}

void Explosion::draw()
{
	fill_rectangle(color_, bounding_);
}
