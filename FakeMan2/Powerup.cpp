#include "Powerup.h"

Powerup::Powerup(float x, float y)
	: Collectible(x, y, COLLECTIBLE_DIM, COLLECTIBLE_DIM, COLOR_ORANGE)
{
}

void Powerup::collect(Player* player)
{
	player->immortalize();
}

void Powerup::draw()
{
	//fill_circle(color_, bounding_.x + bounding_.width / 2, bounding_.y + bounding_.height / 2, bounding_.width / 2);
	load_bitmap("mine", "Resources/mine.png");
	draw_bitmap("mine", bounding_.x-7, bounding_.y-7, option_scale_bmp(0.7, 0.7));
}