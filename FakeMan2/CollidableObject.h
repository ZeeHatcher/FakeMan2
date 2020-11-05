#pragma once
#include "DrawableObject.h"
#include "SwinGame.h"

class CollidableObject
	: public DrawableObject
{
public :
	CollidableObject(float x, float y, int32_t width, int32_t height, color col);
	bool isCollide(CollidableObject* ent);
};
