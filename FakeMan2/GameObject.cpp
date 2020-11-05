#include "GameObject.h"

GameObject::GameObject(float x, float y, int32_t width, int32_t height, color col)
{
	bounding_.x = x;
	bounding_.y = y;
	bounding_.width = width;
	bounding_.height = height;
	color_ = col;
}

// Returns the "hitbox" of the object
rectangle& GameObject::getBounding()
{
	return bounding_;
}