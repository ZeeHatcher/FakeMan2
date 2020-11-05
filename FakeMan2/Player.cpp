#include "Player.h"

Player::Player()
	: MoveableObject(10*TILE_DIM+1, 8*TILE_DIM+1, TILE_DIM-2, TILE_DIM-2, COLOR_YELLOW, 2)
{
	score_ = 0;
	ammo_ = 0;
	// bmp_ = load_bitmap("pacman", "pacman.png");
}

int Player::getAmmo()
{
	return ammo_;
}

int Player::getScore()
{
	return score_;
}

void Player::incrementAmmo()
{
	ammo_++;
}

void Player::incrementScore()
{
	score_++;
}

void Player::dropBomb(std::vector<Bomb*>& bombs)
{
	if (ammo_ > 0)
	{
		float xDiff, yDiff, cellX, cellY;

		xDiff = std::fmod(bounding_.x, TILE_DIM);
		cellX = (xDiff < TILE_DIM / 2) ? bounding_.x - xDiff : bounding_.x - xDiff + TILE_DIM;

		yDiff = std::fmod(bounding_.y, TILE_DIM);
		cellY = (yDiff < TILE_DIM / 2) ? bounding_.y - yDiff : bounding_.y - yDiff + TILE_DIM;

		bombs.push_back(
			new Bomb(
				cellX + (TILE_DIM / 2) - (BOMB_DIM / 2),
				cellY + (TILE_DIM / 2) - (BOMB_DIM / 2)
			)
		);

		ammo_--;
	}
}

void Player::die()
{
	alive_ = false;
}

void Player::draw()
{
	fill_rectangle(color_, bounding_);
}