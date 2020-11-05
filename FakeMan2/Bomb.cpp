#include "Bomb.h"

Bomb::Bomb(float x, float y)
	: DrawableObject(x, y, BOMB_DIM, BOMB_DIM, COLOR_RED)
{
	actualTimeToExplode_ = 2 * 60;
	explosionRadius_ = 2 * TILE_DIM;
}

bool Bomb::canExplode()
{
	return (actualTimeToExplode_ == 0);
}

int Bomb::getActualTimeToExplode()
{
	return actualTimeToExplode_;
}

void Bomb::decrementActualTimeToExplode()
{
	actualTimeToExplode_--;
}

void Bomb::draw()
{
	fill_rectangle(color_, bounding_);
}

void Bomb::explode(std::vector<std::vector<Cell*>>& cells, std::vector<Wall*>& walls, std::vector<Explosion*>& explosions)
{
	rectangle refCellBounding;

	bool refCellFound = false;
	for (int x = 0; x < cells.size(); x++)
	{
		if (refCellFound) break;

		for (int y = 0; y < cells[x].size(); y++)
		{
			rectangle cellBounding = cells[x][y]->getBounding();
			if (
				bounding_.x > cellBounding.x &&
				bounding_.x < cellBounding.x + cellBounding.width &&
				bounding_.y > cellBounding.y &&
				bounding_.y < cellBounding.y + cellBounding.height
			)
			{
				refCellBounding = cellBounding;

				refCellFound = true;
				break;
			}
		}
	}

	for (int i = walls.size() - 1; i >= 0; i--)
	{
		rectangle wallBounding = walls[i]->getBounding();

		float diff = std::sqrt(
			pow(wallBounding.x - refCellBounding.x, 2) + pow(wallBounding.y - refCellBounding.y, 2)
		);

		if (diff <= explosionRadius_)
		{
			delete walls[i];
			walls.erase(walls.begin() + i);
		}
	}

	for (int x = 0; x < cells.size(); x++)
	{
		for (int y = 0; y < cells[x].size(); y++)
		{
			rectangle cellBounding = cells[x][y]->getBounding();

			float diff = std::sqrt(
				pow(cellBounding.x - refCellBounding.x, 2) + pow(cellBounding.y - refCellBounding.y, 2)
			);

			if (diff <= explosionRadius_)
			{
				explosions.push_back(new Explosion(cellBounding.x, cellBounding.y));
			}
		}
	}
}