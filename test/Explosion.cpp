#include "Explosion.h"
#include <iostream>

Explosion::Explosion(float x, float y, bool isDraw)
	: CollidableObject(x, y, TILE_DIM, TILE_DIM, COLOR_ORANGE)
{
	actualTimeToDissipate_ = 10;
	isDraw_ = isDraw;
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
	if (isDraw_)
	{
		bitmap bmp = load_bitmap("explosion", "Resources/explosion.png");
		draw_bitmap("explosion", bounding_.x - bitmap_width(bmp) / 2 + TILE_DIM / 2, bounding_.y - bitmap_height(bmp) / 2 + TILE_DIM / 2);
	}
}
