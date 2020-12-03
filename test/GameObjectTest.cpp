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
		Explosion explosion(10, 20, false);
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
		Player* player = new Player();
		player->moveRight();
		player->draw();
		if (animation_name(player->getAnimation()) != "walk right") {
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
		Player* player = new Player();
		player->draw();
		if (animation_name(player->getAnimation()) != "walk left") {
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
		Player* player = new Player();
		player->immortalize();
		player->moveRight();
		player->draw();
		if (animation_name(player->getAnimation()) != "p walk right") {
			throw;
		}

		std::cout << "successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "failed" << std::endl;
	}
}

void GameObjectTest::testPlayerImmortal()
{
	std::cout << "testPlayerImmortal: ";

	try
	{
        Player* player = new Player();

        if (player->immortal() != false)
        {
            throw;
        }

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testPlayerImmortalize()
{
	std::cout << "testPlayerImmortalize: ";

	try
	{
        Player* player = new Player();

        player->immortalize();

        if (player->immortal() != true)
        {
            throw;
        }

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}

void GameObjectTest::testPowerupCollect()
{
	std::cout << "testPowerupCollect: ";

	try
	{
        Player* player = new Player();
        Powerup* powerup = new Powerup(0, 0);

        powerup->collect(player);

        if (player->immortal() != true)
        {
            throw;
        }

		std::cout << "Successful" << std::endl;
	}
	catch (...)
	{
		std::cout << "Failed" << std::endl;
	}
}
