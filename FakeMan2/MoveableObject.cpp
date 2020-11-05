#include "MoveableObject.h"

MoveableObject::MoveableObject(float x, float y, int32_t width, int32_t height, color col, float speed)
	: CollidableObject(x, y, width, height, col)
{
	speed_ = speed;
	alive_ = true;
}

void MoveableObject::move(int x, int y)
{
	bounding_.x += x * speed_;
	bounding_.y += y * speed_;
}

void MoveableObject::warp(float x, float y)
{
	bounding_.x = x;
	bounding_.y = y;
}

bool MoveableObject::getAlive()
{
	return alive_;
}