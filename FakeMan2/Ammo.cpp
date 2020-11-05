#include "Ammo.h"

Ammo::Ammo(float x, float y)
	: Collectible(x, y, AMMO_DIM, AMMO_DIM, COLOR_PURPLE)
{
}

void Ammo::collect(Player* player)
{
	player->incrementAmmo();
}

void Ammo::draw()
{
	draw_rectangle(color_, bounding_);
}