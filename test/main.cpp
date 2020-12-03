#include <iostream>
#include "splashkit.h"
#include "Game.h"
#include "GameObjectTest.h"

int main()
{
  GameObjectTest runner;

  runner.testAmmoConstructor();
  runner.testBombConstructor();
  runner.testCellConstructor();
  runner.testEnemyConstructor();
  runner.testExplosionConstructor();
  runner.testPlayerMoveAnimation();
  runner.testPlayerInitAnimation();
  runner.testPlayerImmortalAnimation();
  runner.testPlayerImmortal();
  runner.testPlayerImmortalize();
  runner.testPowerupCollect();
}
