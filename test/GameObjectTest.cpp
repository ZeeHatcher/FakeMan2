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
