/***************************************************************************//**
  @file     +handler.c
  @brief    +Handling functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/

#include "handler.h"
#include "allegro.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+

/*******************************************************************************
 *******************************************************************************
                    GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


void initializeElements(Game* game)
{
	#ifdef PC
		initializeAllegro(game);
	#else
		initializeRaspy();
	#endif
}

void destroyElements()
{
	#ifdef PC
		destroyAllegro();
	#else
		destroyRaspy();
	#endif
}

void updateHud(Game* game)
{
	#ifdef PC
		allegroUpdateHud(game);
	#endif
}

void drawHud(Game* game)
{
	#ifdef PC
		allegroDrawHud(game);
	#else
		showLevel(game);
		showNext(game);
	#endif
}

// --- drawing ---

void drawMenu()
{
	#ifdef PC
		allegroDrawMenu();
	#endif
}

// Draws current state of the game

void drawGame(const Game* game)
{
    // Draws static tetrominos
    drawGrid(game);

    // Draws active tetromino
    drawActiveTetromino(game);
}

// Draws static tetrominos

void drawGrid(const Game* game)
{
	#ifdef PC
		allegroDrawGrid(game);
	#else
		draw_board(game);
	#endif
}

// Draws active tetromino

void drawActiveTetromino(const Game* game)
{
	#ifdef PC
		allegroDrawActiveTetromino(game);
	#else
		draw_tetromino(game);
	#endif
}

// Draws game over message

void drawGameOver(long score)
{
	#ifdef PC
		allegroDrawGameOver(score);
	#else
		raspyShowScore(score);
	#endif
}

void drawNewHighScore(long score, int scoreIndex)
{
	#ifdef PC
		allegroDrawHighScore(score, scoreIndex);
	#endif
}

void drawPause(Game* game)
{
	#ifdef PC
		allegroDrawPause();
	#endif
}

void drawUpdatedScore(Game* game)
{
	#ifdef PC
		allegroGetTopScore(game);
	#endif
}

bool movedLeft()
{
	#ifdef PC
		if (allegro->key[ALLEGRO_KEY_LEFT])
			return true;
		else
			return false;
	#else
		jcoord_t coord = joy_get_coord();
		if (coord.x < JOY_MAX_NEG/2){
			return true;
		}
		else
			return false;
	#endif
}

bool movedRight()
{
	#ifdef PC
		if (allegro->key[ALLEGRO_KEY_RIGHT])
			return true;
		else
			return false;
	#else
		jcoord_t coord = joy_get_coord();
		if (coord.x > JOY_MAX_POS/2){
			return true;
		}
		else
			return false;
	#endif
}

bool movedDown()
{
	#ifdef PC
		if (allegro->key[ALLEGRO_KEY_DOWN])
			return true;
		else
			return false;
	#else
		jcoord_t coord = joy_get_coord();
		if (coord.y < JOY_MAX_NEG/2){
			return true;
		}
		else
			return false;
	#endif
}

bool movedUp()
{
	#ifdef PC
		if (allegro->key[ALLEGRO_KEY_UP])
			return true;
		else
			return false;
	#else
		jcoord_t coord = joy_get_coord();
		if (coord.y > JOY_MAX_POS / 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	#endif
}

bool rotated()
{
	#ifdef PC
		if (allegro->key[ALLEGRO_KEY_SPACE])
			return true;
		else
			return false;
	#else
		jswitch_t state = joy_get_switch();
		if (state == J_PRESS){
			return true;
		}
		return false;
	#endif
}

void recover_game(Game* game)
{
	FILE *rescue = fopen("saving.txt", "r");					//Resume an old game
	if(rescue == NULL)
	{
		exit(1);
	}
	for (int i = 0; i < GRID_HEIGHT; i++)
	{							//Puts all saved blocks into the grid
		for(int j= 0; j < GRID_WIDTH ; j++)
		{
			fscanf(rescue, "%d", &(game->grid[i][j]));
		}
	}

	for (int i = 0; i < GRID_HEIGHT; i++)
	{							//Puts all saved tetromino blocks into the current game
		for(int j= 0; j < GRID_WIDTH; j++)
		{
			fscanf(rescue, "%d", &(game->tetrominoGrid[i][j]));
		}
	}
	fscanf(rescue, "%d", &(game->activeTetromino.x));		//Gets state of active tetromino
	fscanf(rescue, "%d", &(game->activeTetromino.y));
	fscanf(rescue, "%d", &(game->activeTetromino.rotation));

	for (int i = 0; i < TETROMINO_H; i++)
	{
		for(int j= 0; j < TETROMINO_W ; j++)
		{
			fscanf(rescue, "%d", &(game->activeTetromino.shape[i][j]));
		}
		printf("\n");
	}
	fscanf(rescue, "%d", &(game->activeTetromino.shapeIndex));
	fscanf(rescue, "%d", &(game->activeTetromino.moveTimer));
	fscanf(rescue, "%d", &(game->activeTetromino.rotateTimer));

	fscanf(rescue, "%d", &(game->nextTetromino.x));		//Gets state of next tetromino
	fscanf(rescue, "%d", &(game->nextTetromino.y));
	fscanf(rescue, "%d", &(game->nextTetromino.rotation));

	for (int i = 0; i < TETROMINO_H; i++)
	{
		for(int j= 0; j < TETROMINO_W; j++)
		{
			fscanf(rescue, "%d", &(game->nextTetromino.shape[i][j]));
		}
	}
	fscanf(rescue, "%d", &(game->nextTetromino.shapeIndex));
	fscanf(rescue, "%d", &(game->nextTetromino.moveTimer));
	fscanf(rescue, "%d", &(game->nextTetromino.rotateTimer));

	fscanf(rescue, "%ld", &(game->score));		//Gets other game values
	fscanf(rescue, "%d", &(game->level));
	for (int i = 0; i < NUM_SHAPES; i++)
	{
		fscanf(rescue, "%d", &(game->statistics[i]));
	}
	fclose(rescue);
}

void save_game(Game* game)
{
	FILE *save = fopen("saving.txt", "w");					//Save the current game
	if(save == NULL)
	{
		exit(1);
	}
	for (int i = 0; i < GRID_HEIGHT; i++)
	{							//Puts all saved blocks into saving.txt
		for(int j= 0; j < GRID_WIDTH; j++)
		{
			fprintf(save, "%d ", (game->grid[i][j]));
			printf("%d\t", game->grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");printf("\n");
	for (int i = 0; i < GRID_HEIGHT; i++)
	{							//Puts all saved tetromino blocks into the saving.txt
		for(int j= 0; j < GRID_WIDTH; j++)
		{
			fprintf(save, "%d ", (game->tetrominoGrid[i][j]));
			printf("%d\t", game->tetrominoGrid[i][j]);
		}
		printf("\n");
	}
	fprintf(save, "%d", (game->activeTetromino.x));		//Saves state of active tetromino
	printf("\nactiveTetromino.x %d\t", game->activeTetromino.x);

	fprintf(save, "%d", (game->activeTetromino.y));
	printf("\nactiveTetromino.y %d\t", game->activeTetromino.y);

	fprintf(save, "%d", (game->activeTetromino.rotation));
	printf("\nactiveTetromino.rotation %d\t\n", game->activeTetromino.rotation);

	for (int i = 0; i < TETROMINO_H; i++)
	{
		for(int j= 0; j < TETROMINO_W ; j++)
		{
			fprintf(save, "%d", (game->activeTetromino.shape[i][j]));
			printf("%d\t", game->activeTetromino.shape[i][j]);
		}
		printf("\n");
	}
	fprintf(save, "%d", (game->activeTetromino.shapeIndex));
	printf("\nctiveTetromino.shapeIndex %d\t", game->activeTetromino.shapeIndex);

	fprintf(save, "%d", (game->activeTetromino.moveTimer));
	printf("\nctiveTetromino.moveTimer %d\t", game->activeTetromino.moveTimer);

	fprintf(save, "%d", (game->activeTetromino.rotateTimer));
	printf("\nctiveTetromino.rotateTimer %d\t", game->activeTetromino.rotateTimer);

	fprintf(save, "%d", (game->nextTetromino.x));		//Saves state of next tetromino
	printf("\nnextTetromino.x %d\t", game->nextTetromino.x);

	fprintf(save, "%d", (game->nextTetromino.y));
	printf("\nnextTetromino.y %d\t", game->nextTetromino.y);

	fprintf(save, "%d", (game->nextTetromino.rotation));
	printf("\nextTetromino.rotation %d\t\n", game->nextTetromino.rotation);

	for (int i = 0; i < TETROMINO_H; i++)
	{
		for(int j= 0; j < TETROMINO_W ; j++)
		{
			fprintf(save, "%d", (game->nextTetromino.shape[i][j]));
			printf("%d\t", game->nextTetromino.shape[i][j]);
		}
		printf("\n");
	}
	fprintf(save, "%d", (game->nextTetromino.shapeIndex));
	printf("\nnextTetromino.shapeIndex %d\t", game->nextTetromino.shapeIndex);

	fprintf(save, "%d", (game->nextTetromino.moveTimer));
	printf("\nnextTetromino.moveTimer %d\t", game->nextTetromino.moveTimer);

	fprintf(save, "%d", (game->nextTetromino.rotateTimer));
	printf("\nnextTetromino.rotateTimer %d\t", game->nextTetromino.rotateTimer);

	fprintf(save, "%ld", (game->score));		//Saves other game values
	printf("\n%ld\t", game->score);

	fprintf(save, "%d", (game->level));
	printf("\n%d\t\n", game->level);

	for (int i = 0; i < 7; i++)
	{
		fprintf(save, "%d", (game->statistics[i]));
		printf("%d\t", game->statistics[i]);
	}
	fclose(save);
}
void updateColorMap(Game* game, int row, int col)
{
	#ifdef PC
		allegroUpdateColorMap(game, row, col);
	#endif
}

void playSoundIndex(int soundIndex)
{
	#ifdef PC
		allegroPlaySound(soundIndex);
	#else
		raspyPlaySound(soundIndex);
	#endif
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
