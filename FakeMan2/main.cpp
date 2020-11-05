#include <stdio.h>
#include "splashkit.h"
#include "Game.h"

int main()
{
    open_window("Hello World", 800, 600);
    // show_swin_game_splash_screen();

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
