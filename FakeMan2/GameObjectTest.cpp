#include "GameObjectTest.h"

void GameObjectTest::testAmmoConstructor()
{
	std::cout << "testAmmoConstructor: ";

	try
	{
		Ammo ammo(10, 20);
		GameObject obj = (GameObject)ammo;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testBombConstructor()
{
	std::cout << "testBombConstructor: ";

	try
	{
		Bomb bomb(10, 20);
		GameObject obj = (GameObject)bomb;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testCellConstructor()
{
	std::cout << "testCellConstructor: ";

	try
	{
		Cell cell(10, 20);
		GameObject obj = (GameObject)cell;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testEnemyConstructor()
{
	std::cout << "testEnemyConstructor: ";

	try
	{
		Enemy enemy(10, 20, ColorBlack, 1, 2);
		GameObject obj = (GameObject)enemy;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testExplosionConstructor()
{
	std::cout << "testExplosionConstructor: ";

	try
	{
		Explosion explosion(10, 20);
		GameObject obj = (GameObject)explosion;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testPlayerConstructor()
{
	std::cout << "testPlayerConstructor: ";

	try
	{
		Player player;
		GameObject obj = (GameObject)player;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testWallConstructor()
{
	std::cout << "testWallConstructor: ";

	try
	{
		Wall wall(10, 20);
		GameObject obj = (GameObject)wall;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testAmmoGetBounding()
{
	std::cout << "testAmmoGetBounding: ";

	try
	{
		bool testPass = false;

		float x = 10;
		float y = 20;

		Ammo ammo(x, y);

		rectangle bounding = ammo.getBounding();

		testPass = (bounding.x == x && bounding.y == y);
		if (!testPass) throw;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testBombGetBounding()
{
	std::cout << "testBombGetBounding: ";

	try
	{
		bool testPass = false;

		float x = 10;
		float y = 20;

		Bomb bomb(x, y);

		rectangle bounding = bomb.getBounding();

		testPass = (bounding.x == x && bounding.y == y);
		if (!testPass) throw;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testCellGetBounding()
{
	std::cout << "testCellGetBounding: ";

	try
	{
		bool testPass = false;

		float x = 10;
		float y = 20;

		Cell cell(x, y);

		rectangle bounding = cell.getBounding();

		testPass = (bounding.x == x && bounding.y == y);
		if (!testPass) throw;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testEnemyGetBounding()
{
	std::cout << "testEnemyGetBounding: ";

	try
	{
		bool testPass = false;

		float x = 10;
		float y = 20;

		Enemy enemy(x, y, ColorBlack, 1, 2);

		rectangle bounding = enemy.getBounding();

		testPass = (bounding.x == x + 1 && bounding.y == y + 1);
		if (!testPass) throw;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testExplosionGetBounding()
{
	std::cout << "testExplosionGetBounding: ";

	try
	{
		bool testPass = false;

		float x = 10;
		float y = 20;

		Explosion explosion(x, y);

		rectangle bounding = explosion.getBounding();

		testPass = (bounding.x == x && bounding.y == y);
		if (!testPass) throw;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testPlayerGetBounding()
{
	std::cout << "testPlayerGetBounding: ";

	try
	{
		bool testPass = false;

		Player player;

		rectangle bounding = player.getBounding();

		testPass = (bounding.x == 10 * TILE_DIM + 1 && bounding.y == 8 * TILE_DIM + 1);
		if (!testPass) throw;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testWallGetBounding()
{
	std::cout << "testWallGetBounding: ";

	try
	{
		bool testPass = false;

		float x = 10;
		float y = 20;

		Wall wall(x, y);

		rectangle bounding = wall.getBounding();

		testPass = (bounding.x == x && bounding.y == y);
		if (!testPass) throw;

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}
