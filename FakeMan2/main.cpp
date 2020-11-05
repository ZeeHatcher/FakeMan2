#include <iostream>
#include "splashkit.h"
#include "Game.h"

int main()
{

    open_window("FakeMan", WINDOW_WIDTH, WINDOW_HEIGHT);
    // show_swin_game_splash_screen();

	// **********
	// ** Main **
	// **********
    Game game;
    
    do
    {
        process_events();
        
        clear_screen(COLOR_BLACK);
        
        game.update();
        game.draw();
        
        refresh_screen(60);
    } while (!quit_requested());
    
    return 0;
}
