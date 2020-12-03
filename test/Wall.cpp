#include "Wall.h"

Wall::Wall(float x, float y)
	: Wall(x, y, COLOR_GRAY)
{
}

Wall::Wall(float x, float y, color clr)
	: CollidableObject(x, y, TILE_DIM, TILE_DIM, clr)
{
}

void Wall::draw()
{
	//draw_rectangle(color_, bounding_);

	/*This function is called to display destructable walls*/
	load_bitmap("wall", "Resources/neon_cube.png");
	draw_bitmap("wall", bounding_.x-5, bounding_.y-5,option_scale_bmp(0.7,0.7));
}

void Wall::drawbdr()
{
	/*This function is called to display indestructable walls*/
	load_bitmap("border", "Resources/border.png");
	draw_bitmap("border", bounding_.x - 5, bounding_.y - 5, option_scale_bmp(0.7, 0.7));
}