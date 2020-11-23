#include "Ammo.h"

Ammo::Ammo(float x, float y)
	: Collectible(x, y, COLLECTIBLE_DIM, COLLECTIBLE_DIM, COLOR_CYAN)
{
}

void Ammo::collect(Player* player)
{
	player->incrementAmmo();
}

void Ammo::draw()
{
	fill_circle(color_, bounding_.x + bounding_.width / 2, bounding_.y + bounding_.height / 2, bounding_.width / 2);
}