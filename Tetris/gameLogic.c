/***************************************************************************//**
  @file     +gameLogic.c
  @brief    +Game logic constants and functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/

#include "gameLogic.h"
#include "handler.h"

#include <stdio.h>
#include <stdbool.h>


/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/

#define LEADERBOARD_FILE "leaderboard.txt"
#define LEADERBOARD_SIZE 10
#define MAX_NAME_LENGTH 6


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

#ifdef PC
static void allegroGameLoop(Game* game);
static void allegroMenuLoop(Game* game);
#else
static void raspyGameLoop(Game* game);
static void raspyMenuLoop (Game* game);
#endif

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

void menuLoop(Game* game)
{
#ifdef PC
    allegroMenuLoop(game);
#else
	raspyMenuLoop (game);
#endif
}

#ifdef PC
static void allegroMenuLoop(Game* game)
{
    ALLEGRO_EVENT event;

    al_wait_for_event(allegro->eventQueue, &event);

    allegroUpdateKeyboard(&event);

    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
        game->redraw = true;
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        game->quit = true;
        break;

    default:
        break;
    }

    if (game->redraw && al_is_event_queue_empty(allegro->eventQueue))
    {
        allegroDisplayPreDraw(allegro->buffer);

        drawMenu();

        allegroDisplayPostDraw(allegro->display, allegro->buffer);

        if (rotated())
        {
            game->menu = false;
        }

        game->redraw = false;
    }
}
#else
static void raspyMenuLoop (Game* game)
{
	pauseAudio();
	joyUpdateValues();
	raspyMenu(game);
	if (movedRight())
	{
		unpauseAudio();
		game->menu = false;
		disp_clear();
		disp_update();
	}
	else if (movedLeft())
	{
		game->quit = true;
		game->menu = false;
		disp_clear();
		disp_update();
	}
}

#endif

void gameLoop(Game* game)
{
#ifdef PC
    allegroGameLoop(game);
#else
	raspyGameLoop(game);
#endif
}

#ifdef PC

static void allegroGameLoop(Game* game)
{
    ALLEGRO_EVENT event;

    al_wait_for_event(allegro->eventQueue, &event);

    allegroUpdateKeyboard(&event);

    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
        updateGame(game);
        updateMovement(game);
        updateHud(game);

        if (allegro->key[ALLEGRO_KEY_ESCAPE])
            game->pause = true;

        while (game->pause)
        {
            allegroDisplayPreDraw(allegro->buffer);

            drawHud(game);

            drawGame(game);

            drawPause(game);

            allegroDisplayPostDraw(allegro->display, allegro->buffer);

            al_wait_for_event(allegro->eventQueue, &event);

            allegroUpdateKeyboard(&event);
            if (movedUp(game))
            {
                initializeGame(game);
                break;
            }
            else if (movedDown(game))
            {
                game->pause = false;
                break;
            }
            else if (movedLeft(game))
            {
                initializeGame(game);
                game->menu = true;
                break;
            }
            else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                game->quit = true;
                break;
            }
        }

        game->redraw = true;
        game->frames++;
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        game->quit = true;
        break;

    default:
        break;
    }

    if (game->redraw && al_is_event_queue_empty(allegro->eventQueue))
    {

        allegroDisplayPreDraw(allegro->buffer);

        drawHud(game);

        drawGame(game);

        if (game->gameOver)
        {
            drawGameOver(game->score);
            if (game->highScoreIndex)
            {
                drawNewHighScore(game->score, game->highScoreIndex);
            }
        }

        allegroDisplayPostDraw(allegro->display, allegro->buffer);

        game->redraw = false;
    }

}

#else

static void raspyGameLoop(Game* game) 
{
	game->frames += 10;
	updateGame(game);
    joyUpdateValues();

	updateMovement(game);
	
	drawHud(game);
	drawGame(game);
	
	game->pause = checkPasue ();
	while (game->pause)
	{
		joyUpdateValues();
		if(checkResume())
		{
			break;
		}
		else if(checkRestart())
		{
			initializeGame(game);
			game->menu = false;
			break;
		}
		else if(checkQuit())
		{
			initializeGame(game);
			clearDisp();
			break;
		}
	}
	if(game->waitingForExit){
		while (!checkRestart()){
			joyUpdateValues();
			drawGameOver(game->score);	
		}
		initializeGame(game);
	}
}

#endif



// --- game ---

// Sets initial game state

void initializeGame(Game* game)
{
    #ifdef PC
    if (!game->frames)
	{
    	game->menu = true;
	}
	else
	{
		game->menu = false;
	}
	#else
	game->menu = true;
	#endif
	
    game->gameOver = false;
    game->frames = 0;
    game->score = 0;
    game->highScoreIndex = 0;
    game->level = 0;
    game->lines = 0;
    game->levelCheckpoint = 10 * (game->level + 1);
    game->fixDelay = 0;
    game->waitingForExit = false;
    game->quit = false;
    game->pause = false;
    game->redraw = true; 

    drawUpdatedScore();

    int i;
    for (i = 0; i < NUM_SHAPES; i++)
    {
        game->statistics[i] = 0;
    }

    // Initialize the game grid with zeros
    for (i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            game->grid[i][j] = 0;
            game->tetrominoGrid[i][j] = 0;
        }
    }

    // Generate a new random tetromino
    generateNewTetromino(game);
}

// Updates game state

void updateGame(Game* game)
{
    // Check for game over conditions
    if (isGameOver(game))
    {
        game->gameOver = true;
        if (!game->waitingForExit)
        {
            game->waitingForExit = true;
            
            playSoundIndex(GAME_OVER);
            
            updateLeaderboard(game);
        }
    }

    else
    {
        // Check if the active tetromino can move down
        if (canMoveDown(game))
        {
            if (!(game->frames % ((FPS - game->level * 2 > 0) ? (FPS - game->level * 2) : 1)))
            {
                // Move the tetromino down
                game->activeTetromino.y++;
            }
        }
        else
        {
            if (game->fixDelay)
                game->fixDelay--;
            else
            {
                game->fixDelay += FIX_DELAY;
                // Fix the tetromino in its current position on the game grid
                fixTetromino(game);

                // Check for completed rows and clear them
                clearRows(game);

                // Generate a new random tetromino shape and position
                generateNewTetromino(game);
            }
        }
    }
}

// Updates position of active tetromino

void updateMovement(Game* game)
{
    if (game->activeTetromino.moveTimer)
        game->activeTetromino.moveTimer--;
    else
    {
        #ifdef PC
    	game->activeTetromino.moveTimer += KEY_DELAY;
		#endif
        if (movedLeft())
        {
            if (canMoveSideways(game, -1)) // Move tetromino right
            {
                game->activeTetromino.x--;
                playSoundIndex(MOVE_SIDEWAYS);
            }
        }
        else if (movedRight())
        {
            if (canMoveSideways(game, 1)) // Move tetromino right
            {
                game->activeTetromino.x++;
                playSoundIndex(MOVE_SIDEWAYS);
            }
        }
        else if (movedDown())
        {
            if (canMoveDown(game))
                game->activeTetromino.y++;
            ; // Move tetromino down
        }
    }
    if (game->activeTetromino.rotateTimer)
        game->activeTetromino.rotateTimer--;
    else if (rotated())
    {
        #ifdef PC
		game->activeTetromino.rotateTimer += KEY_DELAY;
		#endif
        rotateTetromino(game); // Rotate tetromino when spacebar is pressed
    }
}

// Updates game level

void updateLevel(Game* game)
{
    if (game->lines >= game->levelCheckpoint)
    {
        game->level++;
        game->levelCheckpoint += 10;
    }
}

// Rotates the tetromino 90 degrees clockwise

void rotateTetromino(Game* game)
{
    // Create a copy of the current tetromino position and rotation
    int oldX = game->activeTetromino.x;
    int oldY = game->activeTetromino.y;
    int oldRotation = game->activeTetromino.rotation;
    int newRotation = (oldRotation + 1) % 4;

    // Check if the new rotation is valid
    bool canRotate = true;
    int i;
    int j;
    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (tetrominoShapes[game->activeTetromino.shapeIndex][newRotation][i][j] != 0)
            {
                int row = game->activeTetromino.y + i;
                int col = game->activeTetromino.x + j;
                if (col < 0 || col >= GRID_WIDTH || row <= -1 || row >= GRID_HEIGHT || (row >= 0 && game->grid[row][col] != 0))
                {
                    canRotate = false;
                    break;
                }
            }
        }
        if (!canRotate)
        {
            break;
        }
    }

    if (canRotate)
    {
        // Update the rotation of the tetromino
        game->activeTetromino.rotation = newRotation;
        for (i = 0; i < TETROMINO_H; i++)
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                game->activeTetromino.shape[i][j] = tetrominoShapes[game->activeTetromino.shapeIndex][newRotation][i][j];
            }
        }
        playSoundIndex(ROTATE);
    }
}

bool canMoveSideways(Game* game, int xOffset)
{
    // Calculate the new x coordinate for the tetromino
    int newX = game->activeTetromino.x + xOffset;

    // Check if the tetromino can move horizontally in the specified direction
    bool canMove = true;
    int rotation = game->activeTetromino.rotation;

    int i;
    int j;
    for (i = TETROMINO_H - 1; i >= 0; i--)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                int row = game->activeTetromino.y + i;
                int col = newX + j;

                // Check if the new position is out of bounds or collides with existing blocks
                if (col < 0 || col >= GRID_WIDTH || row >= GRID_HEIGHT || (row >= 0 && game->grid[row][col] != 0))
                {
                    canMove = false;
                    break;
                }
            }
        }

        if (!canMove)
        {
            break;
        }
    }

    return canMove;
}

// Check if the active tetromino can move down

bool canMoveDown(const Game* game)
{
    int rotation = game->activeTetromino.rotation;
    int i;
    int j;
    // Check if any cells below the tetromino are occupied or if it has reached the bottom
    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                int row = game->activeTetromino.y + i + 1;
                int col = game->activeTetromino.x + j;
                if (row >= GRID_HEIGHT || game->grid[row][col] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Fix the tetromino in its current position on the game grid

void fixTetromino(Game* game)
{
    int i;
    int j;
    // Update the game grid with the tetromino's occupied cells
    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                int row = game->activeTetromino.y + i;
                int col = game->activeTetromino.x + j;
                game->grid[row][col] = 1;
                updateColorMap(game, row, col);
            }
        }
    }
    playSoundIndex(FIX);
}

// Check for completed rows and clear them

void clearRows(Game* game)
{
    int numClearedRows = 0;

    int i;
    int j;
    int k;

    for (i = GRID_HEIGHT - 1; i >= 0; i--)
    {
        bool isRowFull = true;

        for (j = 0; j < GRID_WIDTH; j++)
        {
            if (game->grid[i][j] == 0)
            {
                isRowFull = false;
                break;
            }
        }

        if (isRowFull)
        {
            // Shift all rows above the cleared row down by one
            for (k = i; k > 0; k--)
            {
                for (j = 0; j < GRID_WIDTH; j++)
                {
                    game->grid[k][j] = game->grid[k - 1][j];
                    game->tetrominoGrid[k][j] = game->tetrominoGrid[k - 1][j];
                }
            }

            // Clear the top row
            for (j = 0; j < GRID_WIDTH; j++)
            {
                game->grid[0][j] = 0;
            }

            numClearedRows++;
            i++;
        }
    }

    updateScore(game, numClearedRows);
    game->lines += numClearedRows;

    if (numClearedRows)
        updateLevel(game);
}

// Update game score based on the number of rows cleared and the current level

void updateScore(Game* game, int numClearedRows)
{
    switch (numClearedRows)
    {
    case 1:
        game->score += 40 * (game->level + 1);
        playSoundIndex(BURN);
        break;
    case 2:
        game->score += 100 * (game->level + 1);
        playSoundIndex(BURN);
        break;
    case 3:
        game->score += 300 * (game->level + 1);
        playSoundIndex(BURN);
        break;
    case 4:
        game->score += 1200 * (game->level + 1);
        playSoundIndex(TETRIS);
        break;
    default:
        break;
    }
}

// Generate a new random tetromino

void generateNewTetromino(Game* game)
{
    // Randomly select a shape index for the new tetromino
    int shapeIndex = rand() % NUM_SHAPES;
    if (game->frames)
    {
        // Update the active tetromino with the new shape and position

        if (game->nextTetromino.shapeIndex == I)
        {
            game->activeTetromino.x = game->nextTetromino.x - 1;
            game->activeTetromino.y = game->nextTetromino.y - 1;
        }
        else
        {
            game->activeTetromino.x = game->nextTetromino.x;
            game->activeTetromino.y = game->nextTetromino.y;
        }
        copyShape(game->nextTetromino.shape, game, true);
        game->activeTetromino.shapeIndex = game->nextTetromino.shapeIndex;
        game->activeTetromino.rotation = game->nextTetromino.rotation;
        game->activeTetromino.moveTimer = game->nextTetromino.moveTimer;
        game->activeTetromino.rotateTimer = game->nextTetromino.rotateTimer;
        game->statistics[game->nextTetromino.shapeIndex]++;

        // Update the active tetromino with the new shape and position
        game->nextTetromino.x = GRID_WIDTH / 2 - 1;
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);
        game->nextTetromino.shapeIndex = shapeIndex;
        game->nextTetromino.rotation = 0;
        game->nextTetromino.moveTimer = 0;
        game->nextTetromino.rotateTimer = 0;
    }
    else
    {
        // Update the active tetromino with the new shape and position
        game->nextTetromino.x = GRID_WIDTH / 2 - 1;
        game->nextTetromino.y = 0;
        copyShape(tetrominoShapes[shapeIndex][0], game, false);
        game->nextTetromino.shapeIndex = shapeIndex;
        game->nextTetromino.rotation = 0;
        game->nextTetromino.moveTimer = 0;
        game->nextTetromino.rotateTimer = 0;

        // Randomly select a shape index for the new tetromino
        shapeIndex = rand() % NUM_SHAPES;

        // Update the active tetromino with the new shape and position
        if (shapeIndex == I)
        {
            game->activeTetromino.x = GRID_WIDTH / 2 - 2;
            game->activeTetromino.y = -1;
        }
        else
        {
            game->activeTetromino.x = GRID_WIDTH / 2 - 1;
            game->activeTetromino.y = 0;
        }
        copyShape(tetrominoShapes[shapeIndex][0], game, true);
        game->activeTetromino.shapeIndex = shapeIndex;
        game->activeTetromino.rotation = 0;
        game->activeTetromino.moveTimer = 0;
        game->activeTetromino.rotateTimer = 0;
        game->statistics[shapeIndex]++;
    }
}

// Check if the game is over

bool isGameOver(const Game* game)
{
    if (!game->fixDelay)
    {
        int rotation = game->activeTetromino.rotation;

        int i;
        int j;
        // Check if any cells in the starting position are occupied
        for (i = 0; i < TETROMINO_H; i++)
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                if (game->activeTetromino.shape[i][j] != 0)
                {
                    int row = game->activeTetromino.y + i;
                    int col = game->activeTetromino.x + j;
                    if (game->grid[row][col] != 0)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void updateLeaderboard(Game* game) 
{
    // Read current leaderboard from file
    FILE* file = fopen(LEADERBOARD_FILE, "r");
    if (file == NULL) 
    {
        printf("Error opening leaderboar file for reading\n");
        exit(EXIT_FAILURE);
    }

    int leaderboard[LEADERBOARD_SIZE] = {0};
    int i;

    for (i = 0; i < LEADERBOARD_SIZE; ++i) 
    {
        if (fscanf(file, "%d", &leaderboard[i]) == EOF)
        {
            printf("Error reading from leaderboar file\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);

    // Insert new score
    int j;

    for (i = 0; i < LEADERBOARD_SIZE; ++i) 
    {
        if (game->score > leaderboard[i]) 
        {
            game->highScoreIndex = i + 1;
            // Shift the leaderboard to make room for the new score
            for (int j = LEADERBOARD_SIZE - 1; j > i; --j) 
            {
                leaderboard[j] = leaderboard[j - 1];
            }

            // Insert the new score at the correct position
            leaderboard[i] = game->score;
            break;
        }
    }

    // Write updated leaderboard back to the file
    file = fopen(LEADERBOARD_FILE, "w");
    if (file == NULL) 
    {
        printf("Error opening leaderboard file for writing\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < LEADERBOARD_SIZE; ++i) 
    {
        fprintf(file, "%d\n", leaderboard[i]);
    }

    fclose(file);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


