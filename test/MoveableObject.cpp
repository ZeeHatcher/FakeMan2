#include "MoveableObject.h"

MoveableObject::MoveableObject(float x, float y, int32_t width, int32_t height, color col, float speed)
	: CollidableObject(x, y, width, height, col)
{
	speed_ = speed;
	alive_ = true;
}

// Moves the object in the specified direction with the given speed
void MoveableObject::move(int x, int y)
{
	bounding_.x += x * speed_;
	bounding_.y += y * speed_;
}

// Teleports the object to the given position
void MoveableObject::warp(float x, float y)
{
	bounding_.x = x;
	bounding_.y = y;
}

// Returns the alive state of object
bool MoveableObject::getAlive()
{
	return alive_;
}