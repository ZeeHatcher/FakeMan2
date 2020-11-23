#pragma once
#include <cmath>
#include <vector>
#include "Bomb.h"
#include "Dimensions.h"
#include "MoveableObject.h"
#include "splashkit.h"

class Player
	: public MoveableObject
{
public :
	Player();
	bool immortal();
	int getAmmo();
	int getScore();
	void decrementTimeImmortal();
	void deimmortalize();
	void immortalize();
	void incrementAmmo();
	void incrementScore();
	void dropBomb(std::vector<Bomb*>& bombs);
	void die();
	void draw();

private :
	int score_;
	int ammo_;
	int timeImmortal_;
};
