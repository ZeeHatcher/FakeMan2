#include "Bomb.h"

Bomb::Bomb(float x, float y)
	: DrawableObject(x, y, BOMB_DIM, BOMB_DIM, COLOR_RED)
{
	actualTimeToExplode_ = 2 * 60;
	explosionRadius_ = 3 * TILE_DIM; 
}

// Returns whether the Bomb can explode
bool Bomb::canExplode()
{
	return (actualTimeToExplode_ == 0);
}

// Decrement counter if Bomb cannot explode yet
void Bomb::decrementActualTimeToExplode()
{
	actualTimeToExplode_--;
}

void Bomb::draw()
{
	/*if (actualTimeToExplode_<120) {*/
		/*Display an icon showing the the button has been clicked
		* when the count down has started
		suggesting that the player has detonated the bomb*/
	load_bitmap("detonate", "Resources/detonate.png");
	//}
	///*Display an icon showing the the button that has not been clicked*/
	//bitmap_= load_bitmap("detonator", "Resources/detonator.png");
	
	draw_bitmap("detonate", bounding_.x - 5, bounding_.y - 5);
}

// Destroys Wall objects within explosion radius and spawns Explosion objects in that same area
void Bomb::explode(std::vector<std::vector<Cell*>>& cells, std::vector<Wall*>& walls, std::vector<Explosion*>& explosions)
{
	// Finding the Cell that contains the Bomb object
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

	// Checks for Walls within the explosion radius and deletes them from the map
	for (int i = walls.size() - 1; i >= 0; i--)
	{
		rectangle wallBounding = walls[i]->getBounding();

		// Euclidean distance between Wall and Bomb
		float diff = std::sqrt(
			pow(wallBounding.x - refCellBounding.x, 2) + pow(wallBounding.y - refCellBounding.y, 2)
		);

		if (diff <= explosionRadius_)
		{
			delete walls[i];
			walls.erase(walls.begin() + i);
		}
	}

	// Generates Explosion objects within explosion radius
	for (int x = 0; x < cells.size(); x++)
	{
		for (int y = 0; y < cells[x].size(); y++)
		{
			rectangle cellBounding = cells[x][y]->getBounding();

			// Euclidean distance between Cell and Bomb
			float diff = std::sqrt(
				pow(cellBounding.x - refCellBounding.x, 2) + pow(cellBounding.y - refCellBounding.y, 2)
			);

			if (diff <= explosionRadius_)
			{
				bool isDraw = (std::abs(refCellBounding.x - cellBounding.x) < 1 && std::abs(refCellBounding.y - cellBounding.y) < 1);

				explosions.push_back(new Explosion(cellBounding.x, cellBounding.y, isDraw));
			}
		}
	}
}