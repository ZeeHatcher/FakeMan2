#include "Enemy.h"
#include <algorithm>
#include <cmath>
#include <iostream>

// Initializes Enemy at a specific part of the map
// Width and height is "TILE_DIM - 2" to prevent collision with edge of walls
Enemy::Enemy(float x, float y, color col, float speed, int timeToNextMove)
	: MoveableObject(x+1, y+1, TILE_DIM-2, TILE_DIM-2, col, speed)
{
	respawnPos_.x = x + 1;
	respawnPos_.y = y + 1;
	timeToRespawn_ = actualTimeToRespawn_ = 10 * 60;
	direction_ = Direction::Null;
	possibleDirections_ = {};
	randomTimer_ = 0;
	alive_ = false;
}

// Returns whether the Enemy can change direction
bool Enemy::canMove(std::vector<Wall*>& borders, std::vector<Wall*>& walls)
{
	// 4 initial possible directions
	std::vector<Direction> directions = { Direction::Up, Direction::Down, Direction::Left, Direction::Right };
	rectangle origBounding = bounding_; // Saves current position of Enemy to reset back later

	for (int i = directions.size() - 1; i >= 0; i--)
	{
		bool isOccupied = false;

		// Move a specific direction depending on the 4 initial possible direction
		switch (directions[i])
		{
		case Direction::Up:
			MoveableObject::move(0, -1);
			break;

		case Direction::Down:
			MoveableObject::move(0, 1);
			break;

		case Direction::Left:
			MoveableObject::move(-1, 0);
			break;

		case Direction::Right:
			MoveableObject::move(1, 0);
			break;
		}

		// Checks if chosen direction collides with a Wall
		for (int i = 0; i < borders.size(); i++)
		{
			if (isOccupied) break;

			if (isCollide(borders[i]))
			{
				isOccupied = true;
				break;
			}
		}

		for (int i = 0; i < walls.size(); i++)
		{
			if (isOccupied) break;

			if (isCollide(walls[i]))
			{
				isOccupied = true;
				break;
			}
		}

		// Removes chosen direction from the list of possible directions 
		if (isOccupied)
		{
			directions.erase(directions.begin() + i);
		}

		// Reset position back to original position to test other directions
		bounding_ = origBounding;
	}

	// Can move from spawn
	if (getBounding().x == respawnPos_.x && getBounding().y == respawnPos_.y) {
		possibleDirections_ = directions;
		return true;
	}

	// Count how many paths are available
	int openPaths = directions.size();

	// Intersection
	if (openPaths == 3) {
		// Get invert direction of direction
		switch (getDirection()) {
			case Direction::Up:
				directions.erase(std::remove(directions.begin(), directions.end(), Direction::Down), directions.end());
				break;
			case Direction::Down:
				directions.erase(std::remove(directions.begin(), directions.end(), Direction::Up), directions.end());
				break;
			case Direction::Left:
				directions.erase(std::remove(directions.begin(), directions.end(), Direction::Right), directions.end());
				break;
			case Direction::Right:
				directions.erase(std::remove(directions.begin(), directions.end(), Direction::Left), directions.end());
				break;

		}
		possibleDirections_ = directions;
		return true;
	}
	// Corner
	else if (openPaths == 2 && !(std::find(directions.begin(), directions.end(), direction_) != directions.end()))
	{
		possibleDirections_ = directions;
		return true;
	}
	if (openPaths == 1) 
	{
		possibleDirections_ = directions;
		return true;
	}
	return false;
}

// Returns whether the Enemy can respawn
bool Enemy::canRespawn()
{
	return (actualTimeToRespawn_ == 0);
}

// Returns the current move direction of Enemy
Direction Enemy::getDirection()
{
	return direction_;
}

// Algorithm to choose next direction to move towards
void Enemy::chooseNextMove(rectangle& playerBounding, bool immortal)
{
	
	randomTimer_++;
	// Fast ghosts don't chase
	if (speed_ > 2) {
		if (randomTimer_ % 4 == 0) {
			direction_ = possibleDirections_[rand() % possibleDirections_.size()];
			
		}
		return;
	}

	// If all other conditions fail, just go random
	direction_ = possibleDirections_[rand() % possibleDirections_.size()];

	int dist = sqrt(pow((playerBounding.x - getBounding().x), 2) + pow((playerBounding.y - getBounding().y), 2));
	std::vector<Direction> directions = {};
	if (!immortal) {
		if (playerBounding.x - getBounding().x <= 10) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Left) != possibleDirections_.end()) {
				directions.push_back(Direction::Left);
			}
		}
		if (playerBounding.x - getBounding().x >= 10) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Right) != possibleDirections_.end()) {
				directions.push_back(Direction::Right);
			}
		}
		if (playerBounding.y - getBounding().y <= 10) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Up) != possibleDirections_.end()) {
				directions.push_back(direction_ = Direction::Up);
			}
		}
		if (playerBounding.y - getBounding().y >= 10) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Down) != possibleDirections_.end()) {
				directions.push_back(Direction::Down);
			}
		}

	}
	else {
		if (playerBounding.x >= getBounding().x) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Left) != possibleDirections_.end()) {
				directions.push_back(Direction::Left);
			}
		}
		if (playerBounding.x <= getBounding().x) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Right) != possibleDirections_.end()) {
				directions.push_back(Direction::Right);
			}
		}
		if (playerBounding.y >= getBounding().y) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Up) != possibleDirections_.end()) {
				directions.push_back(Direction::Up);
			}
		}
		if (playerBounding.y <= getBounding().y) {
			if (std::find(possibleDirections_.begin(), possibleDirections_.end(), Direction::Down) != possibleDirections_.end()) {
				directions.push_back(Direction::Down);
			}
		}
	}
	if (directions.size() != 0) {
		direction_ = directions[rand() % directions.size()];
	}
}

// Decrement counter if Enemy cannot respawn yet
void Enemy::decrementActualTimeToRespawn()
{
	actualTimeToRespawn_--;
}

// "Kill" the Enemy if collides with Explosion, and resets position to the original spawn point
void Enemy::die()
{
	alive_ = false;
	warp(respawnPos_.x, respawnPos_.y);
	actualTimeToRespawn_ = timeToRespawn_;
}

void Enemy::draw()
{
	//fill_rectangle(color_, bounding_);

	/*Since there is an enemy that moves faster,
	a different bitmap would be used*/
	load_bitmap("enemy1", "Resources/enemy1.png");
	load_bitmap("enemy2", "Resources/enemy2.png");
	
	/*The bitmap used would be determined based on the enemy's speed*/
	if (speed_ > 2) {
		draw_bitmap("enemy1", bounding_.x, bounding_.y);
	}
	else {
		draw_bitmap("enemy2", bounding_.x, bounding_.y);
	}
}

// Move Enemy depending on current move direction
void Enemy::move()
{
	switch (direction_)
	{
	case Direction::Up:
		MoveableObject::move(0, -1);
		break;

	case Direction::Down:
		MoveableObject::move(0, 1);
		break;

	case Direction::Left:
		MoveableObject::move(-1, 0);
		break;

	case Direction::Right:
		MoveableObject::move(1, 0);
		break;
	}
}

// Respawn Enemy
void Enemy::respawn()
{
	alive_ = true;
}
