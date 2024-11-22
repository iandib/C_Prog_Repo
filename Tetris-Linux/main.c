#include "gameLogic.h"
#include "handler.h"

int main()
{

    // Create game instance
    Game game = { 0 };
    //remove("saving.txt");

    // Start Game
    initializeGame(&game);
    //printf("%d", game->leaderboard[0].score);
    initializeElements(&game);
    FILE* save = fopen("saving.txt", "r");
    if(save != NULL){
    	fclose(save);
		game.pause = 1;
		recover_game(&game);
	}
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
