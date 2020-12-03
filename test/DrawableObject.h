#pragma once
#include "GameObject.h"
#include "splashkit.h"

class DrawableObject
	: public GameObject
{
public :
	DrawableObject(float x, float y, int32_t width, int32_t height, color col);
	virtual void draw() = 0;
};
