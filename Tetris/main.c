#include "gameLogic.h"
#include "handler.h"

int main()
{
    initializeElements();

    // Create game instance
    Game game = { 0 };

    // Start Game
    initializeGame(&game);
	
	
	 while (!game.quit)
	 {
        // Menu loop
        while (game.menu && !game.quit)
		{
			menuLoop(&game);
		}
        // Game loop
        while (!game.menu && !game.quit)
        {
            game.gameOver = false;
            while (!game.gameOver && !game.menu && !game.quit)
            {
                gameLoop(&game);
            }
        }
    }
    destroyElements();

    return 0;
}
