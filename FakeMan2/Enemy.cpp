#include "Enemy.h"

Enemy::Enemy(float x, float y, color col, float speed, int timeToNextMove)
	: MoveableObject(x+1, y+1, TILE_DIM-2, TILE_DIM-2, col, speed)
{
	respawnPos_.x = x + 1;
	respawnPos_.y = y + 1;
	timeToNextMove_ = timeToNextMove * 60;
	actualTimeToNextMove_ = 3 * 60;
	timeToRespawn_ = actualTimeToRespawn_ = 10 * 60;
	direction_ = Direction::Null;
}

bool Enemy::canMove()
{
	return (actualTimeToNextMove_ == 0);
}

bool Enemy::canRespawn()
{
	return (actualTimeToRespawn_ == 0);
}

Direction Enemy::getDirection()
{
	return direction_;
}

void Enemy::chooseNextMove(std::vector<Wall*>& borders, std::vector<Wall*>& walls)
{
	std::vector<Direction> directions = { Direction::Up, Direction::Down, Direction::Left, Direction::Right };
	rectangle origBounding = bounding_;

	for (int i = directions.size() - 1; i >= 0; i--)
	{
		bool isOccupied = false;

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

		if (isOccupied)
		{
			directions.erase(directions.begin() + i);
		}

		bounding_ = origBounding;
	}

	direction_ = directions[rand() % directions.size()];
}

void Enemy::decrementActualTimeToNextMove()
{
	actualTimeToNextMove_--;
}

void Enemy::decrementActualTimeToRespawn()
{
	actualTimeToRespawn_--;
}

void Enemy::die()
{
	alive_ = false;
	warp(respawnPos_.x, respawnPos_.y);
	actualTimeToRespawn_ = timeToRespawn_;
}

void Enemy::draw()
{
	fill_rectangle(color_, bounding_);
}

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

void Enemy::resetActualTimeToNextMove()
{
	actualTimeToNextMove_ = timeToNextMove_;
}

void Enemy::respawn()
{
	alive_ = true;
}

void Enemy::skipActualTimeToNextMove()
{
	actualTimeToNextMove_ = 0;
}
