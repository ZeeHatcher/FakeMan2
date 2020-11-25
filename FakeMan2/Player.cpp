#include "Player.h"

// Initializes Player object at a specific part of the map
// Width and height is "TILE_DIM - 2" to prevent collision with edge of walls
Player::Player()
	: MoveableObject(MAP_WIDTH / 2 * TILE_DIM - TILE_DIM / 2, 17 * TILE_DIM + 1, TILE_DIM - 2, TILE_DIM - 2, COLOR_YELLOW, 2)
{
	score_ = 0;
	ammo_ = 1;
	timeImmortal_ = false;

	//Load the sprites sheet for the pac man's different movements
	sprites_ = load_bitmap("pacman", "Resources/spritesheet.png");

	//separate the sprite sheet into 12 icons based on the scale
	bitmap_set_cell_details(sprites_, 14, 14, 24, 1, 24);

	//Load the animation script
	script_ = load_animation_script("Pacman", "pac_sprites.txt");

	//Initially, the animation for left waking would be set
	animation_ = create_animation(script_, "walk left");

	//Link the bitmap with the animation
	opts_ = option_with_animation(animation_);
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
	/*fill_rectangle(color_, bounding_);*/
	draw_bitmap(sprites_, bounding_.x, bounding_.y, opts_);
}

void Player::updateAnim() {
	/*function called to update the animation after specific intervals*/
	update_animation(animation_);
}

void Player::moveUp() {
	//Load the animation labeled walk up in the animation script
	if (immortal()) {
		if (animation_name(animation_) != "p walk up") {
			assign_animation(animation_, "p walk up");
		}
	}
	else {
		if (animation_name(animation_) != "walk up") {
			assign_animation(animation_, "walk up");
		}
	}
}

void Player::moveLeft() {
	//Load the animation labeled walk left in the animation script
	/*if (animation_name(animation_) != "walk left") {
		assign_animation(animation_, "walk left");
	}*/
	if (immortal()) {
		if (animation_name(animation_) != "p walk left") {
			assign_animation(animation_, "p walk left");
		}
	}
	else {
		if (animation_name(animation_) != "walk left") {
			assign_animation(animation_, "walk left");
		}
	}
}

void Player::moveDown() {
	//Load the animation labeled walk down in the animation script
	/*if (animation_name(animation_) != "walk down") {
		assign_animation(animation_, "walk down");
	}*/
	if (immortal()) {
		if (animation_name(animation_) != "p walk down") {
			assign_animation(animation_, "p walk down");
		}
	}
	else {
		if (animation_name(animation_) != "walk down") {
			assign_animation(animation_, "walk down");
		}
	}
}

void Player::moveRight() {
	//Load the animation labeled walk right in the animation script
	/*if (animation_name(animation_) != "walk right") {
		assign_animation(animation_, "walk right");
	}*/
	if (immortal()) {
		if (animation_name(animation_) != "p walk right") {
			assign_animation(animation_, "p walk right");
		}
	}
	else {
		if (animation_name(animation_) != "walk right") {
			assign_animation(animation_, "walk right");
		}
	}
}