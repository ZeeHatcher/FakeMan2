#pragma once
#include <sstream>
#include <vector>
#include "Ammo.h"
#include "Bomb.h"
#include "Cell.h"
#include "Collectible.h"
#include "CollidableObject.h"
#include "Difficulty.h"
#include "Direction.h"
#include "DrawableObject.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Food.h"
#include "GameObject.h"
#include "MoveableObject.h"
#include "Player.h"
#include "Powerup.h"
#include "Status.h"
#include "Wall.h"

// TEST
#include <iostream>
#include <stdio.h>
using namespace std;

class Game
{
public :
	Game();
	void update();
	void draw();

private :
	void clear();
	void init();
	void initCells(int widthSpan, int heightSpan);
	void initCollectibles();
	void initMap();
	void initBorders(int x, int y, int widthSpan, int heightSpan);
	void initWalls(int x, int y, int widthSpan, int heightSpan);
	void updateMidGame();
	void updatePostGame();
	void updatePreGame();
	
	Player* player_;
	Status status_;
	Difficulty difficulty_;
	std::vector<Bomb*> bombs_;
	std::vector<std::vector<Cell*>> cells_;
	std::vector<Collectible*> collectibles_;
	std::vector<Enemy*> enemies_;
	std::vector<Explosion*> explosions_;
	std::vector<Wall*> borders_;
	std::vector<Wall*> walls_;
};
