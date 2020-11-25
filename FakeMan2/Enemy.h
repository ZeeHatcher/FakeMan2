#pragma once
#include <cstdlib>
#include <vector>
#include "Dimensions.h"
#include "Direction.h"
#include "MoveableObject.h"
#include "splashkit.h"
#include "Wall.h"

class Enemy
	: public MoveableObject
{
public :
	Enemy(float x, float y, color col, float speed, int timeToNextMove);
	bool canMove(std::vector<Wall*>& borders, std::vector<Wall*>& walls);
	bool canRespawn();
	Direction getDirection();
	void chooseNextMove(rectangle& playerBounding);
	void decrementActualTimeToRespawn();
	void die();
	void draw();
	void move();
	void respawn();

private :
	Direction direction_;
	int timeToRespawn_;
	int actualTimeToRespawn_;
	point_2d respawnPos_;
	std::vector<Direction> possibleDirections_;
	int randomTimer_;
};
