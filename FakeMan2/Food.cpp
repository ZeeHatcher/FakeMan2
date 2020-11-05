#include "Food.h"

Food::Food(float x, float y)
	: Collectible(x, y, FOOD_DIM, FOOD_DIM, ColorWhite)
{
}

// Increment Player score if Food is collected
void Food::collect(Player* player)
{
	player->incrementScore();
}

void Food::draw()
{
	fill_circle(color_, bounding_.x + bounding_.width / 2, bounding_.y + bounding_.height / 2, bounding_.width / 2);
}