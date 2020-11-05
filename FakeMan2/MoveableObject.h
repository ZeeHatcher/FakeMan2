#pragma once
#include "CollidableObject.h"
#include "splashkit.h"

class MoveableObject
	: public CollidableObject
{
public :
	MoveableObject(float x, float y, int32_t width, int32_t height, color col, float speed);
	void move(int x, int y);
	void warp(float x, float y);
	bool getAlive();
	virtual void die() = 0;

protected :
	float speed_;
	bool alive_;
};
