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
	bool canMove();
	bool canRespawn();
	Direction getDirection();
	int getTimeToNextMove();
	int getTimeToRespawn();
	void chooseNextMove(std::vector<Wall*>& borders, std::vector<Wall*>& walls);
	void decrementActualTimeToNextMove();
	void decrementActualTimeToRespawn();
	void die();
	void draw();
	void move();
	void resetActualTimeToNextMove();
	void respawn();
	void skipActualTimeToNextMove();

private :
	Direction direction_;
	int timeToNextMove_;
	int actualTimeToNextMove_;
	int timeToRespawn_;
	int actualTimeToRespawn_;
	point2d respawnPos_;
};
