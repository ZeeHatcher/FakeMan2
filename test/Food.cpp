#include "Food.h"

Food::Food(float x, float y)
	: Collectible(x, y, FOOD_DIM, FOOD_DIM, COLOR_WHITE)
{
}

// Increment Player score if Food is collected
void Food::collect(Player* player)
{
	player->incrementScore();
}

void Food::draw()
{
	//fill_circle(color_, bounding_.x + bounding_.width / 2, bounding_.y + bounding_.height / 2, bounding_.width / 2);
	load_bitmap("food", "Resources/dia.png");
	draw_bitmap("food", bounding_.x-5, bounding_.y-5);
}