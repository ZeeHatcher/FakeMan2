#include "Food.h"

Food::Food(float x, float y)
	: Collectible(x, y, FOOD_DIM, FOOD_DIM, COLOR_WHITE)
{
}

void Food::collect(Player* player)
{
	player->incrementScore();
}

void Food::draw()
{
	draw_rectangle(color_, bounding_);
}