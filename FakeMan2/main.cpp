#include <iostream>
#include "SwinGame.h"
#include "Game.h"
#include "GameObjectTest.h"

int main()
{

    open_graphics_window("FakeMan", WINDOW_WIDTH, WINDOW_HEIGHT);
    // show_swin_game_splash_screen();

	// ****************
	// ** Unit Tests **
	// ****************
	std::cout << "---| GameObjectTest |---" << endl;

	// Tests constructor for derived classes and tests if they are derived from GameObject
	GameObjectTest::testAmmoConstructor();
	GameObjectTest::testBombConstructor();
	GameObjectTest::testCellConstructor();
	GameObjectTest::testEnemyConstructor();
	GameObjectTest::testExplosionConstructor();
	GameObjectTest::testPlayerConstructor();
	GameObjectTest::testWallConstructor();

	// Tests getBounding() function of derived classes
	GameObjectTest::testAmmoGetBounding();
	GameObjectTest::testBombGetBounding();
	GameObjectTest::testCellGetBounding();
	GameObjectTest::testEnemyGetBounding();
	GameObjectTest::testExplosionGetBounding();
	GameObjectTest::testPlayerGetBounding();
	GameObjectTest::testWallGetBounding();

	// **********
	// ** Main **
	// **********
    Game game;
    
    do
    {
        process_events();
        
        clear_screen(ColorBlack);
        
        game.update();
        game.draw();
		
		draw_framerate(0,0);
        
        refresh_screen(60);
    } while ( ! window_close_requested() );
    
    release_all_resources();
    return 0;
}
