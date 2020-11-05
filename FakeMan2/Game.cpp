#include "Game.h"

Game::Game()
{
	initCells(MAP_WIDTH, MAP_HEIGHT);
    initMap();
	initCollectibles();
	enemies_ = {
		new Enemy(MAP_WIDTH / 2 * TILE_DIM, MAP_HEIGHT / 2 * TILE_DIM, COLOR_MAGENTA, 3, 1),
		new Enemy(MAP_WIDTH / 2 * TILE_DIM, MAP_HEIGHT / 2 * TILE_DIM, COLOR_PURPLE, 2, 2),
		new Enemy(MAP_WIDTH / 2 * TILE_DIM, MAP_HEIGHT / 2 * TILE_DIM, COLOR_PURPLE, 2, 2)
	};
	player_ = new Player();
}

void Game::update()
{
	if (player_->getAlive() == false)
	{
	}

	for (int i = explosions_.size() - 1; i >= 0; i--)
	{
		Explosion* exp = explosions_[i];

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

	for (int i = 0; i < enemies_.size(); i++)
	{
		if (player_->isCollide(enemies_[i]))
		{
			player_->die();
		}
	}

	for (int i = bombs_.size() - 1; i >= 0; i--)
	{
		Bomb* bomb = bombs_[i];

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

	for (int i = 0; i < enemies_.size(); i++)
	{
		Enemy* e = enemies_[i];

		if (e->getAlive() == true)
		{
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

				break;
			}
		}
		else
		{
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

	// Player Movement
	rectangle& playerBounding = player_->getBounding();

	if (key_down(LEFT_KEY))
	{
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
	}

	if (key_down(RIGHT_KEY))
	{
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
	}

	if (key_down(UP_KEY))
	{
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

	if (key_typed(SPACE_KEY))
	{
		player_->dropBomb(bombs_);
	}
}

void Game::draw()
{
	for (int i = 0; i < collectibles_.size(); i++)
	{
		collectibles_[i]->draw();
	}

	for (int i = 0; i < explosions_.size(); i++)
	{
		explosions_[i]->draw();
	}

	for (int i = 0; i < bombs_.size(); i++)
	{
		bombs_[i]->draw();
	}

    for (int i = 0; i < borders_.size(); i++)
    {
        borders_[i]->draw();
    }

	for (int i = 0; i < walls_.size(); i++)
	{
		walls_[i]->draw();
	}

	for (int i = 0; i < enemies_.size(); i++)
	{
		enemies_[i]->draw();
	}

	player_->draw();
}

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

void Game::initCollectibles()
{
	int maxPlayableX = cells_.size() - 1;
	for (int x = 1; x < maxPlayableX; x++)
	{
		int maxPlayableY = cells_[x].size() - 1;
		for (int y = 1; y < maxPlayableY; y++)
		{
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
				if (
					(x == 1 && y == 1) ||
					(x == maxPlayableX - 1 && y == 1) ||
					(x == 1 && y == maxPlayableY - 1) ||
					(x == maxPlayableX - 1 && y == maxPlayableY - 1)
				)
				{
					collectibles_.push_back(
						new Ammo(
							cellBounding.x + (cellBounding.width / 2) - (AMMO_DIM / 2),
							cellBounding.y + (cellBounding.height / 2) - (AMMO_DIM / 2)
						)
					);
				}
				else
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
	}
}

void Game::initMap()
{
    // Init "indestructible" borders
	for (int x = 0; x < cells_.size(); x++)
	{
		if (x == 0 || x == cells_.size() - 1)
		{
			for (int y = 0; y < cells_[x].size(); y++)
			{
				rectangle cellBounding = cells_[x][y]->getBounding();
				borders_.push_back(new Wall(cellBounding.x, cellBounding.y, COLOR_BLUE));
			}
		}
		else
		{
			rectangle cellBounding;

			cellBounding = (cells_[x].front())->getBounding();
			borders_.push_back(new Wall(cellBounding.x, cellBounding.y, COLOR_BLUE));

			cellBounding = (cells_[x].back())->getBounding();
			borders_.push_back(new Wall(cellBounding.x, cellBounding.y, COLOR_BLUE));
		}
	}

    // Init "destructible" walls
	initWalls(9, 5, 1, 0);
	initWalls(9, 7, 1, 0);
	initWalls(7, 2, 0, 8);
	initWalls(2, 2, 4, 0);
	initWalls(1, 4, 4, 0);
	initWalls(2, 6, 4, 0);
	initWalls(1, 8, 4, 0);
	initWalls(2, 10, 4, 0);
	initWalls(10, 1, 0, 2);
	initWalls(10, 9, 0, 2);
}

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