#pragma once
#include <iostream>
#include "Ammo.h"
#include "Bomb.h"
#include "Cell.h"
#include "Enemy.h"
#include "Explosion.h"
#include "GameObject.h"
#include "Player.h"
#include "Swingame.h"
#include "Wall.h"

class GameObjectTest
{
public :
	static void testAmmoConstructor();
	static void testBombConstructor();
	static void testCellConstructor();
	static void testEnemyConstructor();
	static void testExplosionConstructor();
	static void testPlayerConstructor();
	static void testWallConstructor();

	static void testAmmoGetBounding();
	static void testBombGetBounding();
	static void testCellGetBounding();
	static void testEnemyGetBounding();
	static void testExplosionGetBounding();
	static void testPlayerGetBounding();
	static void testWallGetBounding();
};