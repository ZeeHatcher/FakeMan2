#pragma once
#include <iostream>
#include "Ammo.h"
#include "Bomb.h"
#include "Enemy.h"
#include "Cell.h"
#include "Explosion.h"
#include "Player.h"
<<<<<<< Updated upstream
=======
#include "Powerup.h"
>>>>>>> Stashed changes

class GameObjectTest
{
public :
	static void testAmmoConstructor();
	static void testBombConstructor();
	static void testCellConstructor();
	static void testEnemyConstructor();
	static void testExplosionConstructor();
	static void testPlayerInitAnimation();
	static void testPlayerImmortalAnimation();
	static void testPlayerMoveAnimation();
        static void testPlayerImmortal();
        static void testPlayerImmortalize();
        static void testPowerupCollect();
};
