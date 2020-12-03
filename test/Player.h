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
        animation getAnimation();
	void decrementTimeImmortal();
	void deimmortalize();
	void immortalize();
	void incrementAmmo();
	void incrementScore();
	void dropBomb(std::vector<Bomb*>& bombs);
	void die();
	void draw();
	void moveRight();
	void moveUp();
	void moveLeft();
	void moveDown();
	void updateAnim();

private :
	int score_;
	int ammo_;
	int timeImmortal_;
	animation animation_;
	drawing_options opts_;
	animation_script script_;
	bitmap sprites_;
};
