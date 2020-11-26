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
		Enemy enemy(10, 20, COLOR_BLACK, 1, 2);
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

void GameObjectTest::testPlayerMoveAnimation()
{
	std::cout << "testPlayerMoveAnimation: ";

	try
	{
		player* player();
		player->moveRight();
		player->Draw();
		if (animation_name(player.animation_) != "walk right") {
			throw;
		}

		std::cout << "successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "failed" << std::endl;
	}
}

void GameObjectTest::testPlayerInitAnimation()
{
	std::cout << "testPlayerMoveAnimation: ";

	try
	{
		player* player();
		player->Draw();
		if (animation_name(player.animation_) != "walk left") {
			throw;
		}

		std::cout << "successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "failed" << std::endl;
	}
}

void GameObjectTest::testPlayerImmortalAnimation()
{
	std::cout << "testPlayerImmortalAnimation: ";

	try
	{
		player* player();
		player->immortalize();
		player->moveRight();
		player->Draw();
		if (animation_name(player.animation_) != "p walk right") {
			throw;
		}

		std::cout << "successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "failed" << std::endl;
	}
}

