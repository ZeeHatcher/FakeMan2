#include "Player.h"

// Initializes Player object at a specific part of the map
// Width and height is "TILE_DIM - 2" to prevent collision with edge of walls
Player::Player()
	: MoveableObject(MAP_WIDTH / 2 * TILE_DIM - TILE_DIM / 2, 17 * TILE_DIM + 1, TILE_DIM - 2, TILE_DIM - 2, COLOR_YELLOW, 2)
{
	score_ = 0;
	ammo_ = 3;
	timeImmortal_ = false;
}

// Returns the immortal state of Player
bool Player::immortal()
{
	return (timeImmortal_ > 0);
}

// Returns current ammo count of Player
int Player::getAmmo()
{
	return ammo_;
}

// Returns current score of Player
int Player::getScore()
{
	return score_;
}

void Player::decrementTimeImmortal()
{
	timeImmortal_--;
}

void Player::deimmortalize()
{
	color_ = COLOR_YELLOW;
}

void Player::immortalize()
{
	color_ = COLOR_WHITE;
	timeImmortal_ = 5 * 60;
}

// Increment ammo when Ammo object is collected
void Player::incrementAmmo()
{
	ammo_++;
}

// Increment score when Food object is collected
void Player::incrementScore()
{
	score_++;
}

// Creates a new Bomb object after calculating its position snapped to the nearest tile
void Player::dropBomb(std::vector<Bomb*>& bombs)
{
	if (ammo_ > 0)
	{
		float xDiff, yDiff, cellX, cellY;

		// Calculates how far the X position is from the nearest multiple of TILE_DIM and chooses the nearest multiple
		xDiff = std::fmod(bounding_.x, TILE_DIM);
		cellX = (xDiff < TILE_DIM / 2) ? bounding_.x - xDiff : bounding_.x - xDiff + TILE_DIM;

		// Calculates how far the Y position is from the nearest multiple of TILE_DIM and chooses the nearest multiple
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

// "Killing" the player when colliding with Enemy or Explosion
void Player::die()
{
	alive_ = false;
}

void Player::draw()
{
	fill_rectangle(color_, bounding_);
}