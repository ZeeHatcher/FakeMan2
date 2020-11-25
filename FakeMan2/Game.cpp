#include "Game.h"

Game::Game()
{
	init();
}

// Chooses update loop depending on Status
void Game::update()
{
	switch (status_)
	{
	case Status::PreGame:
		updatePreGame();
		break;

	case Status::MidGame:
		updateMidGame();
		break;

	case Status::PostGame:
		updatePostGame();
		break;
	}
}

// Main update loop for all the game mechanics
void Game::updateMidGame()
{
	// Win/Lose condition
	// Win if all Collectibles are collected
	// Lose if player dies
	if (player_->getAlive() == false || collectibles_.empty())
	{
		status_ = Status::PostGame;
	}

	// Update explosions
	for (int i = explosions_.size() - 1; i >= 0; i--)
	{
		Explosion* exp = explosions_[i];

		// Kills player/enemies if they collide with the Explosion
		if (player_->isCollide(exp))
		{
			player_->die();
		}

		for (int j = 0; j < enemies_.size(); j++)
		{
			Enemy* e = enemies_[j];
			if (e->isCollide(exp))
			{
				e->die();
			}
		}

		// Checks if explosion can "disappear" based on the "actualTimeToDissipate" counter
		if (exp->canDissipate())
		{
			delete exp;
			explosions_.erase(explosions_.begin() + i);
		}
		else
		{
			exp->decrementActualTimeToDissipate();
		}
	}

	// Kills Player if it collides with Enemy
	// or if the Player is "immortal", kill the Enemy
	for (int i = 0; i < enemies_.size(); i++)
	{
		if (player_->isCollide(enemies_[i]))
		{
			if (player_->immortal())
			{
				enemies_[i]->die();
			}
			else
			{
				player_->die();
			}
		}
	}

	if (player_->immortal())
	{
		player_->decrementTimeImmortal();
	}
	else
	{
		player_->deimmortalize();
	}

	// Update bombs
	for (int i = bombs_.size() - 1; i >= 0; i--)
	{
		Bomb* bomb = bombs_[i];

		// Checks if bombs can explode based on the "actualTimeToExplode" counter
		if (bomb->canExplode())
		{
			bomb->explode(cells_, walls_, explosions_);
			delete bomb;
			bombs_.erase(bombs_.begin() + i);
		}
		else
		{
			bomb->decrementActualTimeToExplode();
		}
	}

	// Collision checking between Collectibles and Player
	for (int i = collectibles_.size() - 1; i >= 0; i--)
	{
		Collectible* col = collectibles_[i];

		if (player_->isCollide(col))
		{
			col->collect(player_);
			delete col;
			collectibles_.erase(collectibles_.begin() + i);
		}
	}

	// Update enemies
	for (int i = 0; i < enemies_.size(); i++)
	{
		Enemy* e = enemies_[i];

		// Checks if Enemy is alive
		if (e->getAlive() == true)
		{
			// Checks if Enemy can change direction based on the "actualTimeToNextMove" counter
			if (e->canMove())
			{
				e->chooseNextMove(borders_, walls_);
				e->resetActualTimeToNextMove();
			}
			else
			{
				e->decrementActualTimeToNextMove();
			}

			e->move();

			// Checks enemy collision with walls and borders. Reset position to the edge of wall depending on the direction if they collide
			rectangle enemyBounding = e->getBounding();
			switch (e->getDirection())
			{
			case Direction::Up:
				for (int i = 0; i < borders_.size(); i++)
				{
					if (e->isCollide(borders_[i]))
					{
						rectangle wallBounding = borders_[i]->getBounding();
						e->warp(enemyBounding.x, wallBounding.y + wallBounding.height + 1);
						e->skipActualTimeToNextMove();
					}
				}

				for (int i = 0; i < walls_.size(); i++)
				{
					if (e->isCollide(walls_[i]))
					{
						rectangle wallBounding = walls_[i]->getBounding();
						e->warp(enemyBounding.x, wallBounding.y + wallBounding.height + 1);
						e->skipActualTimeToNextMove();
					}
				}

				break;

			case Direction::Down:
				for (int i = 0; i < borders_.size(); i++)
				{
					if (e->isCollide(borders_[i]))
					{
						rectangle wallBounding = borders_[i]->getBounding();
						e->warp(enemyBounding.x, wallBounding.y - enemyBounding.height - 1);
						e->skipActualTimeToNextMove();
					}
				}

				for (int i = 0; i < walls_.size(); i++)
				{
					if (e->isCollide(walls_[i]))
					{
						rectangle wallBounding = walls_[i]->getBounding();
						e->warp(enemyBounding.x, wallBounding.y - enemyBounding.height - 1);
						e->skipActualTimeToNextMove();
					}
				}

				break;

			case Direction::Left:
				for (int i = 0; i < borders_.size(); i++)
				{
					if (e->isCollide(borders_[i]))
					{
						rectangle wallBounding = borders_[i]->getBounding();
						e->warp(wallBounding.x + wallBounding.width + 1, enemyBounding.y);
						e->skipActualTimeToNextMove();
					}
				}

				for (int i = 0; i < walls_.size(); i++)
				{
					if (e->isCollide(walls_[i]))
					{
						rectangle wallBounding = walls_[i]->getBounding();
						e->warp(wallBounding.x + wallBounding.width + 1, enemyBounding.y);
						e->skipActualTimeToNextMove();
					}
				}

				if (e->getBounding().x < 0 - TILE_DIM)
				{
					e->warp(MAP_WIDTH * TILE_DIM, 14 * TILE_DIM + 1);
				}

				break;

			case Direction::Right:
				for (int i = 0; i < borders_.size(); i++)
				{
					if (e->isCollide(borders_[i]))
					{
						rectangle wallBounding = borders_[i]->getBounding();
						e->warp(wallBounding.x - enemyBounding.width - 1, enemyBounding.y);
						e->skipActualTimeToNextMove();
					}
				}

				for (int i = 0; i < walls_.size(); i++)
				{
					if (e->isCollide(walls_[i]))
					{
						rectangle wallBounding = walls_[i]->getBounding();
						e->warp(wallBounding.x - enemyBounding.width - 1, enemyBounding.y);
						e->skipActualTimeToNextMove();
					}
				}

				if (e->getBounding().x > MAP_WIDTH * TILE_DIM)
				{
					e->warp(0 - TILE_DIM, 14 * TILE_DIM + 1);
				}

				break;
			}
		}
		else
		{
			// Checks if Enemy can respawn based on the "actualTimeToRespawn" counter
			if (e->canRespawn())
			{
				e->respawn();
			}
			else
			{
				e->decrementActualTimeToRespawn();
			}
		}
	}

	// Processes keyboard input and checks Player collision with wall. Resets position to edge of wall depending on direction if collide
	rectangle& playerBounding = player_->getBounding();

	if (key_down(LEFT_KEY))
	{
		player_->moveLeft();
		player_->move(-1, 0);

		for (int i = 0; i < borders_.size(); i++)
		{
			if (player_->isCollide(borders_[i]))
			{
				rectangle wallBounding = borders_[i]->getBounding();
				player_->warp(wallBounding.x + wallBounding.width + 1, playerBounding.y);
			}
		}

		for (int i = 0; i < walls_.size(); i++)
		{
			if (player_->isCollide(walls_[i]))
			{
				rectangle wallBounding = walls_[i]->getBounding();
				player_->warp(wallBounding.x + wallBounding.width + 1, playerBounding.y);
			}
		}

		if (playerBounding.x < 0 - TILE_DIM)
		{
			player_->warp(MAP_WIDTH * TILE_DIM, 14 * TILE_DIM + 1);
		}
	}

	if (key_down(RIGHT_KEY))
	{
		player_->moveRight();
		player_->move(1, 0);

		for (int i = 0; i < borders_.size(); i++)
		{
			if (player_->isCollide(borders_[i]))
			{
				rectangle wallBounding = borders_[i]->getBounding();
				player_->warp(wallBounding.x - playerBounding.width - 1, playerBounding.y);
			}
		}

		for (int i = 0; i < walls_.size(); i++)
		{
			if (player_->isCollide(walls_[i]))
			{
				rectangle wallBounding = walls_[i]->getBounding();
				player_->warp(wallBounding.x - playerBounding.width - 1, playerBounding.y);
			}
		}

		if (playerBounding.x > MAP_WIDTH * TILE_DIM)
		{
			player_->warp(0 - TILE_DIM, 14 * TILE_DIM + 1);
		}
	}

	if (key_down(UP_KEY))
	{
		player_->moveUp();
		player_->move(0, -1);

		for (int i = 0; i < borders_.size(); i++)
		{
			if (player_->isCollide(borders_[i]))
			{
				rectangle wallBounding = borders_[i]->getBounding();
				player_->warp(playerBounding.x, wallBounding.y + wallBounding.height + 1);
			}
		}

		for (int i = 0; i < walls_.size(); i++)
		{
			if (player_->isCollide(walls_[i]))
			{
				rectangle wallBounding = walls_[i]->getBounding();
				player_->warp(playerBounding.x, wallBounding.y + wallBounding.height + 1);
			}
		}
	}

	if (key_down(DOWN_KEY))
	{
		player_->moveDown();
		player_->move(0, 1);

		for (int i = 0; i < borders_.size(); i++)
		{
			if (player_->isCollide(borders_[i]))
			{
				rectangle wallBounding = borders_[i]->getBounding();
				player_->warp(playerBounding.x, wallBounding.y - playerBounding.height - 1);
			}
		}

		for (int i = 0; i < walls_.size(); i++)
		{
			if (player_->isCollide(walls_[i]))
			{
				rectangle wallBounding = walls_[i]->getBounding();
				player_->warp(playerBounding.x, wallBounding.y - playerBounding.height - 1);
			}
		}
	}

	// Key for dropping bombs
	if (key_typed(SPACE_KEY))
	{
		if (playerBounding.x > 0 && playerBounding.x < MAP_WIDTH * TILE_DIM - TILE_DIM / 2)
		{
			player_->dropBomb(bombs_);
		}
	}
}

void Game::updatePostGame()
{
	// Restart key
	if (key_typed(R_KEY))
	{
		clear();
		init();
		status_ = Status::PreGame;
	}
}

void Game::updatePreGame()
{
	// Start game key
	if (key_typed(RETURN_KEY))
	{
		int speed;

		switch (difficulty_)
		{
		case Difficulty::Easy:
			speed = 1;
			break;
		case Difficulty::Normal:
			speed = 2;
			break;
		case Difficulty::Hard:
			speed = 3;
			break;
		}

		int spawnX = MAP_WIDTH / 2 * TILE_DIM - TILE_DIM / 2;
		int spawnY = 11 * TILE_DIM;

		enemies_ = {
			new Enemy(spawnX, spawnY, COLOR_MAGENTA, 1.5 * speed, 1),
			new Enemy(spawnX, spawnY, COLOR_PURPLE, 1 * speed, 2),
			new Enemy(spawnX, spawnY, COLOR_PURPLE, 1 * speed, 2)
		};

		status_ = Status::MidGame;
	}

	if (key_typed(NUM_1_KEY))
	{
		difficulty_ = Difficulty::Easy;
	}

	if (key_typed(NUM_2_KEY))
	{
		difficulty_ = Difficulty::Normal;
	}

	if (key_typed(NUM_3_KEY))
	{
		difficulty_ = Difficulty::Hard;
	}
}

// Loops through every game object and draws them onto the screen
void Game::draw()
{
	// Draw game objects
	for (int i = 0; i < collectibles_.size(); i++)
	{
		collectibles_[i]->draw();
	}

    for (int i = 0; i < borders_.size(); i++)
    {
        borders_[i]->drawbdr();
    }

	for (int i = 0; i < walls_.size(); i++)
	{
		walls_[i]->draw();
	}

	/*for (int i = 0; i < explosions_.size(); i++)
	{
		explosions_[i]->draw();
	}*/

	if (explosions_.size() > 1) {
		explosions_[0]->draw();
	}

	for (int i = 0; i < bombs_.size(); i++)
	{
		bombs_[i]->draw();
	}

	for (int i = 0; i < enemies_.size(); i++)
	{
		enemies_[i]->draw();
	}

	player_->draw();
	player_->updateAnim();

	fill_rectangle(COLOR_BLACK, MAP_WIDTH * TILE_DIM, 0, SIDE, WINDOW_HEIGHT);

	// Draw side menu to keep track of score count and ammo count
	std::stringstream scoreText;
	scoreText << "Score: " << player_->getScore();
	draw_text(scoreText.str().c_str(), COLOR_WHITE, (MAP_WIDTH + 1) * TILE_DIM, 1 * TILE_DIM);

	std::stringstream ammoText;
	ammoText << "Ammo: " << player_->getAmmo();
	draw_text(ammoText.str().c_str(), COLOR_WHITE, (MAP_WIDTH + 1) * TILE_DIM, 2 * TILE_DIM);

	// Draws overlay menu to show info on game if Status is PreGame or PostGame
	if (status_ != Status::MidGame)
	{
		std::vector<std::string> texts;
		rectangle menuBox;
		menuBox.x = WINDOW_WIDTH * 0.125;
		menuBox.y = WINDOW_HEIGHT * 0.125;
		menuBox.width = WINDOW_WIDTH * 0.75;
		menuBox.height = WINDOW_HEIGHT * 0.75;

		switch (status_)
		{
			case Status::PreGame:
			{
				string difficultyString;

				switch (difficulty_)
				{
				case Difficulty::Easy:
					difficultyString = "Easy";
					break;
				case Difficulty::Normal:
					difficultyString = "Normal";
					break;
				case Difficulty::Hard:
					difficultyString = "Hard";
					break;
				}

				texts = {
					"Welcome To FakeMan, the PacMan replica.",
					"ARROW KEYS to move, SPACEBAR to drop Bombs when you have Ammo.",
					"Collect all the drops to win.",
					"Touching an Enemy or an Explosion tile will result in a Game Over.",
					"Good luck and have fun!",
					"",
					"Press the corresponding keys to change the difficulty to",
					"Easy (1), Normal (2), or Hard (3).",
					"",
					string("Selected difficulty: ").append(difficultyString),
					"",
					"Press the ENTER key to start..."
				};

				break;
			}

			case Status::PostGame:
			{
				texts = {
					scoreText.str(),
					"",
					"Press R to try again..."
				};
				
				if (player_->getAlive() == true)
				{
					texts.insert(texts.begin(), "Victory!");
				}
				else
				{
					texts.insert(texts.begin(), "Game Over!");
				}

				break;
			}
		}
		
		fill_rectangle(COLOR_BLACK, menuBox);
		draw_rectangle(COLOR_RED, menuBox);

		for (int i = 0; i < texts.size(); i++)
		{
			const char* txt = texts[i].c_str();
			float textX = menuBox.x + 20;
			float textY = menuBox.y + 20 + 10 * i;

			draw_text(txt, COLOR_WHITE, textX, textY);
		}
	}
}

// Clear all game objects from memory and arrays to reset
void Game::clear()
{
	delete player_;
	player_ = nullptr;

	for (int i = 0; i < bombs_.size(); i++)
	{
		delete bombs_[i];
	}
	bombs_ = {};

	for (int i = 0; i < cells_.size(); i++)
	{
		for (int j = 0; j < cells_[i].size(); j++)
		{
			delete cells_[i][j];
		}
	}
	cells_ = {};

	for (int i = 0; i < collectibles_.size(); i++)
	{
		delete collectibles_[i];
	}
	collectibles_ = {};

	for (int i = 0; i < enemies_.size(); i++)
	{
		delete enemies_[i];
	}
	enemies_ = {};

	for (int i = 0; i < explosions_.size(); i++)
	{
		delete explosions_[i];
	}
	explosions_ = {};

	for (int i = 0; i < borders_.size(); i++)
	{
		delete borders_[i];
	}
	borders_ = {};

	for (int i = 0; i < walls_.size(); i++)
	{
		delete walls_[i];
	}
	walls_ = {};
}

// Initialize game objects
void Game::init()
{
	initCells(MAP_WIDTH, MAP_HEIGHT);
    initMap();
	initCollectibles();
	player_ = new Player();
	status_ = Status::PreGame;
	difficulty_ = Difficulty::Normal;
}

// Initializes area of cells/tiles
void Game::initCells(int widthSpan, int heightSpan)
{
	for (int x = 0; x < widthSpan; x++)
	{
		cells_.push_back(std::vector<Cell*>());
		for (int y = 0; y < heightSpan; y++)
		{
			cells_[x].push_back(new Cell(x * TILE_DIM, y * TILE_DIM));
		}
	}
}

// Fills empty parts of the map with Collectibles
void Game::initCollectibles()
{
	int maxPlayableX = cells_.size() - 1;
	for (int x = 1; x < maxPlayableX; x++)
	{
		int maxPlayableY = cells_[x].size() - 1;
		for (int y = 1; y < maxPlayableY; y++)
		{
			// Checks if there is a Wall object exactly in the place of the Cell position
			bool isOccupied = false;
			rectangle cellBounding = cells_[x][y]->getBounding();

			for (int n = 0; n < walls_.size(); n++)
			{
				rectangle wallBounding = walls_[n]->getBounding();

				if (cellBounding.x == wallBounding.x && cellBounding.y == wallBounding.y)
				{
					isOccupied = true;
					break;
				}
			}

			if (!isOccupied)
			{
				for (int n = 0; n < borders_.size(); n++)
				{
					rectangle wallBounding = borders_[n]->getBounding();

					if (cellBounding.x == wallBounding.x && cellBounding.y == wallBounding.y)
					{
						isOccupied = true;
						break;
					}
				}
			}

			if (!isOccupied)
			{
				collectibles_.push_back(
					new Food(
						cellBounding.x + (cellBounding.width / 2) - (FOOD_DIM / 2),
						cellBounding.y + (cellBounding.height / 2) - (FOOD_DIM / 2)
					)
				);
			}
		}
	}

	collectibles_.push_back(
		new Powerup(
			TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			3 * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);

	collectibles_.push_back(
		new Powerup(
			(MAP_WIDTH - 2) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			3 * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);

	collectibles_.push_back(
		new Powerup(
			TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			(MAP_HEIGHT - 8) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);

	collectibles_.push_back(
		new Powerup(
			(MAP_WIDTH - 2) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			(MAP_HEIGHT - 8) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);

	collectibles_.push_back(
		new Ammo(
			9 * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			11 * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);

	collectibles_.push_back(
		new Ammo(
			9 * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			(MAP_HEIGHT - 11) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);

	collectibles_.push_back(
		new Ammo(
			(MAP_WIDTH - 10) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			11 * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);

	collectibles_.push_back(
		new Ammo(
			(MAP_WIDTH - 10) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2),
			(MAP_HEIGHT - 11) * TILE_DIM + (TILE_DIM / 2) - (COLLECTIBLE_DIM / 2)
		)
	);
}

void Game::initMap()
{
	// Init "indestructible" border walls
	// Top half
	initBorders(0, 0, MAP_WIDTH / 2 - 1, 0);
	initBorders(0, 1, 0, 7);
	initBorders(13, 1, 0, 3);
	initBorders(0, 9, 5, 4);

	// Bottom half
	initBorders(0, MAP_HEIGHT - 1, MAP_WIDTH / 2 - 1, 0);
	initBorders(1, MAP_HEIGHT - 7, 1, 1);
	initBorders(0, MAP_HEIGHT - 11, 0, 9);
	initBorders(0, MAP_HEIGHT - 16, 5, 4);

	initWalls(10, 12, 7, 4);

	// Init "destructible" walls
	// Top half
	initWalls(2, 2, 3, 2);
	initWalls(7, 2, 4, 2);
	initWalls(2, 6, 3, 1);
	initWalls(7, 6, 1, 7);
	initWalls(10, 6, 3, 1);
	initWalls(13, 8, 0, 2);
	initWalls(9, 9, 2, 1);

	// Bottom half
	initWalls(2, MAP_HEIGHT - 4, 9, 1);
	initWalls(13, MAP_HEIGHT - 5, 0, 2);
	initWalls(7, MAP_HEIGHT - 7, 1, 2);
	initWalls(10, MAP_HEIGHT - 7, 3, 1);
	initWalls(4, MAP_HEIGHT - 8, 1, 2);
	initWalls(2, MAP_HEIGHT - 10, 3, 1);
	initWalls(7, MAP_HEIGHT - 10, 4, 1);
	initWalls(10, MAP_HEIGHT - 13, 3, 1);
	initWalls(13, MAP_HEIGHT - 11, 0, 2);
	initWalls(7, MAP_HEIGHT - 16, 1, 4);
}

// Convenient function to ease the creation of entire lines of Wall objects
void Game::initWalls(int x, int y, int widthSpan, int heightSpan)
{
	for (int n = x; n < x + widthSpan + 1; n++)
	{
		if (n >= cells_.size()) break;

		for (int m = y; m < y + heightSpan + 1; m++)
		{
			if (m >= cells_[n].size()) break;

			rectangle cellBounding = cells_[n][m]->getBounding();
			walls_.push_back(new Wall(cellBounding.x, cellBounding.y));	
		}
	}	

	for (int n = cells_.size() - x - 1; n > cells_.size() - x - widthSpan - 2; n--)
	{
		for (int m = y; m < y + heightSpan + 1; m++)
		{
			rectangle cellBounding = cells_[n][m]->getBounding();
			walls_.push_back(new Wall(cellBounding.x, cellBounding.y));	
		}
	}
}


// Convenient function to ease the creation of entire lines of Wall objects
void Game::initBorders(int x, int y, int widthSpan, int heightSpan)
{
	for (int n = x; n < x + widthSpan + 1; n++)
	{
		if (n >= cells_.size()) break;

		for (int m = y; m < y + heightSpan + 1; m++)
		{
			if (m >= cells_[n].size()) break;

			rectangle cellBounding = cells_[n][m]->getBounding();
			borders_.push_back(new Wall(cellBounding.x, cellBounding.y, COLOR_BLUE));
		}
	}

	for (int n = cells_.size() - x - 1; n > cells_.size() - x - widthSpan - 2; n--)
	{
		for (int m = y; m < y + heightSpan + 1; m++)
		{
			rectangle cellBounding = cells_[n][m]->getBounding();
			borders_.push_back(new Wall(cellBounding.x, cellBounding.y, COLOR_BLUE));
		}
	}
}