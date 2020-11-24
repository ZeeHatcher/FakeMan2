#include "Explosion.h"

Explosion::Explosion(float x, float y)
	: CollidableObject(x, y, TILE_DIM, TILE_DIM, COLOR_ORANGE)
{
	actualTimeToDissipate_ = 10;
}

// Returns whether the Explosion can "disappear"
bool Explosion::canDissipate()
{
	return (actualTimeToDissipate_ == 0);
}

// Decrement counter if can't "disappear" yet
void Explosion::decrementActualTimeToDissipate()
{
	actualTimeToDissipate_--;
}

void Explosion::draw()
{
	/*fill_rectangle(color_, bounding_);*/
	load_bitmap("explosion", "Resources/explosion.png");
	draw_bitmap("explosion", bounding_.x-20, bounding_.y-20);
}
