#pragma once
#include "SwinGame.h"

class GameObject
{
public:
	GameObject(float x, float y, int32_t width, int32_t height, color col);
	rectangle& getBounding();

protected:
	rectangle bounding_;
	color color_;
};
