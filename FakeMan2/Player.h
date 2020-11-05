#pragma once
#include <cmath>
#include <vector>
#include "Bomb.h"
#include "Dimensions.h"
#include "MoveableObject.h"
#include "SwinGame.h"

class Player
	: public MoveableObject
{
public :
	Player();
	int getAmmo();
	int getScore();
	void incrementAmmo();
	void incrementScore();
	void dropBomb(std::vector<Bomb*>& bombs);
	void die();
	void draw();

private :
	int score_;
	int ammo_;
};
