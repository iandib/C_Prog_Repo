/*
 * sound.c
 *
 *  Created on: Nov 25, 2024
 *      Author: juani
 */
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "th2_display_sound.h"
#include "th1_gamelogic.h"
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

// --- sprites ---
#define BLOCK_TYPES 4
#define LEVEL_STYLES 10

// --- sound ---

#define MAX_SFX 32

// --- display ---

#define BUFFER_W 256
#define BUFFER_H 224

#define DISPLAY_SCALE 4
#define DISPLAY_W (BUFFER_W * DISPLAY_SCALE)
#define DISPLAY_H (BUFFER_H * DISPLAY_SCALE)

// --- sprites ---

#define BLOCK_W 8
#define BLOCK_H 8

// --- hud ---

#define HUD_OFFSET_X 32
#define MENU_OFFSET_x 289

#define GAME_OFFSET_X 96
#define GAME_OFFSET_Y 40

#define NEXT_OFFSET_X 160
#define NEXT_OFFSET_Y 104

// --- score ---

#define MAX_SCORE 999999

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum blockTypes
{
    WHITE = 0,
    LIGHT,
    DARK,
    STRIPES
};
enum
{												//Vuelvo a definir los valores los keycodes del teclado para Allegro (deberían estar en la librería estandar pero no son reconocidos)
   ALLEGROKEY_B		= 2,
   ALLEGROKEY_C		= 3,
   ALLEGROKEY_Q		= 17,

   ALLEGROKEY_S		= 19,
   ALLEGROKEY_T		= 20,


   ALLEGROKEY_0		= 27,
   ALLEGROKEY_1		= 28,
   ALLEGROKEY_2		= 29,
   ALLEGROKEY_3		= 30,
   ALLEGROKEY_4		= 31,
   ALLEGROKEY_5		= 32,
   ALLEGROKEY_6		= 33,
   ALLEGROKEY_7		= 34,
};

typedef struct
{
    ALLEGRO_BITMAP* _sheet;

    ALLEGRO_BITMAP* blocks[LEVEL_STYLES][BLOCK_TYPES];

    ALLEGRO_BITMAP* level;

    ALLEGRO_BITMAP* hud;

    ALLEGRO_BITMAP* menu;

} SPRITES;

// --- allegro ---
typedef struct
{
    // event queue
    ALLEGRO_EVENT_QUEUE* eventQueue;

    unsigned char key[ALLEGRO_KEY_MAX];

    // display
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* buffer;

    // hud
    ALLEGRO_FONT* font;
    long score_display;

    // sound
    ALLEGRO_SAMPLE* SFX[MAX_SFX];
    ALLEGRO_AUDIO_STREAM* music;

    // sprites
    SPRITES sprites;

    // timer
    ALLEGRO_TIMER* timer;
    ALLEGRO_TIMER* gametimer;

    // score
    long topScore;
    int scoreIndex;

} ALLEGRO_ELEMENTS;



static void allegroDrawHighScore(long score, int scoreIndex);
static void allegroDrawPause(void);
static void allegroDrawGameOver(long score);
static void allegroDrawActiveTetromino(const Game* game, SPRITES* sprites);
static void allegroDrawNextTetromino(const Game* game, SPRITES* sprites);
static void allegroDrawGrid(const Game* game, SPRITES* sprites);
static void allegroDrawMenu(SPRITES* sprites);
static void allegroDrawHud(Game* game, SPRITES* sprites);
static void allegroUpdateHud(Game* game);
static void allegroDisplayPreDraw(ALLEGRO_BITMAP* buffer);
static void allegroDisplayPostDraw(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* buffer);
static void allegroDrawLevel(const Game* game);
static void allegroDrawStatistics(const Game* game, SPRITES* sprites);



static void initializeAllegro(Game* game, SPRITES* sprites);
static void allegroGetTopScore(Game* game);
static void allegroInitializeDisplay(void);
static void allegroInitializeSprites(SPRITES* sprites);
static ALLEGRO_BITMAP* allegroGrabSprite(int x, int y, int w, int h, SPRITES* sprites);
static void allegroInitializeFonts(void);
static void allegroInitializeSound(void);
static void allegroInitializeTimer(void);
static void allegroInitializeEventQueue(void);

static void destroyAllegro(SPRITES* sprites);
static void allegroDestroySound(void);
static void allegroDestroyDisplay(void);
static void allegroDestroySprites(SPRITES* sprites);


static void checkInitialization(bool test, const char* description);

static int compare(const void* p1, const void* p2);
static void update_leaderboard(Game* game);
static void save_game(Game* game);

void initialize_leaderboard(Game* game);
void recover_game(Game* game);
void * th2_display_sound(void* game);
void playSoundIndex(int soundIndex);

extern int tetrominoShapes[NUM_SHAPES][TETROMINO_R][TETROMINO_H][TETROMINO_W];
extern sem_t s;

static ALLEGRO_ELEMENTS allegroElements = { 0 };
static ALLEGRO_ELEMENTS* allegro = &allegroElements;



void * th2_display_sound(void* gamep)
{
	Game* game = gamep;
#ifdef PC
	bool pressed = false;
	SPRITES sprites;
	initializeAllegro(game, &sprites);
	while(!game->quit)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(allegro->eventQueue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			if (event.timer.source == allegro->timer)
			{
				game->redraw = true;
			}
			else if(event.timer.source == allegro->gametimer)
			{
				game->activeTetromino.move_down++;
			}
		}
		else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			allegroUpdateHud(game);
			game->quit = true;
		}
		else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(!pressed)
			{
				//pressed = true;
				if(game->menu)
				{
					switch(event.keyboard.keycode)
					{
						case ALLEGRO_KEY_SPACE:
							game->menu = false;
							game->gameOver = false;
							al_start_timer(allegro->gametimer);
							sem_post(&s);
							break;
					}
				}
				else if(game->pause)
				{
					switch(event.keyboard.keycode)
					{
						case ALLEGRO_KEY_DOWN:
							sem_post(&s);
							game->pause = false;
							al_resume_timer(allegro->gametimer);
							break;

						case ALLEGRO_KEY_UP:
							game->pause = false;
							initializeGame(game);
							generateNewTetromino(game);
							remove("saving.txt");
							al_start_timer(allegro->gametimer);
							sem_post(&s);

							break;

						case ALLEGRO_KEY_LEFT: game->menu = true; break;

						case ALLEGRO_KEY_RIGHT: //saveeeeeee
			            	game->leaderboard[10].score = game->score;
			            	save_game(game);
							 break;
					}
				}
				else if(game->gameOver)
				{
					switch(event.keyboard.keycode)
					{
						case ALLEGRO_KEY_SPACE:
							game->menu = true;
							game->gameOver = false;
							al_stop_timer(allegro->gametimer);
							initializeGame(game);
							generateNewTetromino(game);
							break;
					}
				}
				else
				{

					switch(event.keyboard.keycode)
					{
						case ALLEGRO_KEY_DOWN: game->activeTetromino.move_down++; break;

						case ALLEGRO_KEY_UP: game->activeTetromino.rotate_++; break;

						case ALLEGRO_KEY_LEFT: game->activeTetromino.move_left++; break;

						case ALLEGRO_KEY_RIGHT: game->activeTetromino.move_right++; break;

						case ALLEGRO_KEY_ESCAPE:
							game->pause = true;
							al_stop_timer(allegro->gametimer);
							break;
						case ALLEGRO_KEY_SPACE: game->activeTetromino.move_down += DISPLAY_H; break;

						default: break;
					}
				}
			}
		}
		if (game->redraw && al_is_event_queue_empty(allegro->eventQueue))
		{
			allegroDisplayPreDraw(allegro->buffer);

			if(game->menu)
			{
				allegroDrawMenu(&sprites);
			}
			else if(game->pause)
			{
				allegroDrawPause();
			}
			else if(game->gameOver)
			{
				allegroDrawGameOver(game->score);
				game->leaderboard[10].score = game->score;
	        	if(game->leaderboard[10].score > game->leaderboard[9].score)
	        	{
	        		allegroDrawHighScore(game->score, game->highScoreIndex);
	        		update_leaderboard(game);
	            }
	        	///////////DRAW LEADERBOARD AND RESTART  //////////////////
			}
			else
			{
				allegroDrawHud(game, &sprites);
				allegroDrawGrid(game, &sprites);
				allegroDrawActiveTetromino(game, &sprites);
			}

			allegroDisplayPostDraw(allegro->display, allegro->buffer);
			game->redraw = false;
		}
	}
	destroyAllegro(&sprites);
	pthread_exit(NULL);
#else
#endif
}
void playSoundIndex(int soundIndex)
{
	#ifdef PC
	al_play_sample(allegro->SFX[soundIndex], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	#else
		raspyPlaySound(soundIndex);
	#endif
}

void initialize_leaderboard(Game* game)
{
	FILE *lead = fopen("leaderboard.txt", "r");
	if(lead == NULL)
	{
		exit(1);
	}
	for (int i = 0; i < 10; i++)
	{									//Puts all highscores into the structures of leaderboard
		fscanf(lead, "%s", game->leaderboard[i].name);
		fscanf(lead, "%d", &(game->leaderboard[i].score));
	}
	fclose(lead);
}
static void update_leaderboard(Game* game)
{		//NEW HIGHSCOREEEEEEE
		#ifdef PC
			//allegro_naming(game->leaderboard[10].name);
		#endif
		qsort(game->leaderboard, 10, sizeof(player_t), compare);
		FILE *leader = fopen("leaderboard.txt", "w");
		if(leader == NULL)
		{
			exit(1);
		}
		for(int i=0; i<10; i++)
		{
			fprintf(leader, "%s %u\n", game->leaderboard[i].name, game->leaderboard[i].score);
		}

		fclose(leader);

}

static int compare(const void* p1, const void* p2)
{
	const player_t* pa = p1;
	const player_t* pb = p2;
	if(pa->score > pb->score)
	{
		return -1;
	}
	if(pa->score < pb->score)
	{
		return 1;
	}
	return 0;
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
	game->activeTetromino.rotation--;

	for (int i = 0; i < TETROMINO_H; i++)
	{
		for(int j= 0; j < TETROMINO_W ; j++)
		{
			fscanf(rescue, "%d", &(game->activeTetromino.shape[i][j]));
		}
	}
	fscanf(rescue, "%d", &(game->activeTetromino.shapeIndex));
	fscanf(rescue, "%d", &(game->activeTetromino.move_down));
	fscanf(rescue, "%d", &(game->activeTetromino.move_up));
	fscanf(rescue, "%d", &(game->activeTetromino.move_left));
	fscanf(rescue, "%d", &(game->activeTetromino.move_right));
	fscanf(rescue, "%d", &(game->activeTetromino.rotate_));

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
	fscanf(rescue, "%d", &(game->nextTetromino.move_down));
	fscanf(rescue, "%d", &(game->nextTetromino.move_up));
	fscanf(rescue, "%d", &(game->nextTetromino.move_left));
	fscanf(rescue, "%d", &(game->nextTetromino.move_right));
	fscanf(rescue, "%d", &(game->nextTetromino.rotate_));

	fscanf(rescue, "%ld", &(game->score));		//Gets other game values
	fscanf(rescue, "%d", &(game->level));
	for (int i = 0; i < NUM_SHAPES; i++)
	{
		fscanf(rescue, "%d", &(game->statistics[i]));
	}
	fclose(rescue);
}

static void save_game(Game* game)
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
		}
	}
	for (int i = 0; i < GRID_HEIGHT; i++)
	{							//Puts all saved tetromino blocks into the saving.txt
		for(int j= 0; j < GRID_WIDTH; j++)
		{
			fprintf(save, "%d ", (game->tetrominoGrid[i][j]));
		}
	}
	fprintf(save, "%d ", (game->activeTetromino.x));		//Saves state of active tetromino

	fprintf(save, "%d ", (game->activeTetromino.y));

	fprintf(save, "%d ", (game->activeTetromino.rotation));

	for (int i = 0; i < TETROMINO_H; i++)
	{
		for(int j= 0; j < TETROMINO_W ; j++)
		{
			fprintf(save, "%d ", (game->activeTetromino.shape[i][j]));
		}
	}
	fprintf(save, "%d ", (game->activeTetromino.shapeIndex));

	fprintf(save, "%d ", (game->activeTetromino.move_down));

	fprintf(save, "%d ", (game->activeTetromino.move_up));

	fprintf(save, "%d ", (game->activeTetromino.move_left));

	fprintf(save, "%d ", (game->activeTetromino.move_right));

	fprintf(save, "%d ", (game->activeTetromino.rotate_));


	fprintf(save, "%d ", (game->nextTetromino.x));		//Saves state of next tetromino

	fprintf(save, "%d ", (game->nextTetromino.y));

	fprintf(save, "%d ", (game->nextTetromino.rotation));

	for (int i = 0; i < TETROMINO_H; i++)
	{
		for(int j= 0; j < TETROMINO_W ; j++)
		{
			fprintf(save, "%d ", (game->nextTetromino.shape[i][j]));
		}
	}
	fprintf(save, "%d ", (game->nextTetromino.shapeIndex));

	fprintf(save, "%d ", (game->nextTetromino.move_down));

	fprintf(save, "%d ", (game->nextTetromino.move_up));

	fprintf(save, "%d ", (game->nextTetromino.move_left));

	fprintf(save, "%d ", (game->nextTetromino.move_right));

	fprintf(save, "%d ", (game->nextTetromino.rotate_));

	fprintf(save, "%ld ", (game->score));		//Saves other game values

	fprintf(save, "%d ", (game->level));
	for (int i = 0; i < NUM_SHAPES; i++)
	{
		fprintf(save, "%d ", (game->statistics[i]));
	}
	fclose(save);
}

#ifdef PC

 static void allegroGetTopScore(Game* game){

    if (game->leaderboard[0].score <= MAX_SCORE)
        allegro->topScore = game->leaderboard[0].score;
    else
        allegro->topScore = MAX_SCORE;
}
static void allegroDisplayPreDraw(ALLEGRO_BITMAP* buffer)
{
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
}
static void allegroDisplayPostDraw(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* buffer)
{
    al_set_target_backbuffer(display);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISPLAY_W, DISPLAY_H, 0);

    al_flip_display();
}
static void allegroUpdateHud(Game* game)
{
    if (allegro->score_display <= MAX_SCORE)
    {
        // Resets score display
        if (allegro->score_display > game->score)
        {
            allegro->score_display = 0;
        }

        // Increases score display in steps
        for (long i = 5; i >= 0; i--)
        {
            long diff = 1 << i;
            if (allegro->score_display <= (game->score - diff))
                allegro->score_display += diff;
        }

        // If the score is greater than the maximum displayable score, it shows the maximum
        if (allegro->score_display > MAX_SCORE)
            allegro->score_display = MAX_SCORE;
    }
}

static void allegroDrawHud(Game* game, SPRITES* sprites)
{
    // Draws framing
    al_draw_bitmap(sprites->hud, 0, 0, 0); // @suppress("Field cannot be resolved")

    // Draws score
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        192, 56,
        0,
        "%06ld",
        allegro->score_display
    );

    // Draws completed lines
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        144, 16,
        0,
        "%04d",
        game->lines
    );

    // Draws top score
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        192, 32,
        0,
        "%06ld",
		allegro->topScore
    );

    // Draws next tetromino
    allegroDrawNextTetromino(game, sprites);

    // Draws current level
    allegroDrawLevel(game);

    // Draws lines and tetromino statistics
    allegroDrawStatistics(game, sprites);
}
static void allegroDrawMenu(SPRITES* sprites)
{
    // Draws framing
    al_draw_bitmap(sprites->menu, 0, 0, 0); // @suppress("Field cannot be resolved")

    // Draws text
    al_draw_text(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        42, 146,
        0,
        "PRESS SPACE"
    );
    al_draw_text(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        54, 158,
        0,
        "TO START"
    );
}
static void allegroDrawGrid(const Game* game, SPRITES* sprites)
{
    int blockCode;
    int i;
    int j;
    for (i = 0; i < GRID_HEIGHT; i++)
    {
        for (j = 0; j < GRID_WIDTH; j++)
        {
            if (game->grid[i][j] != 0)
            {
                blockCode = game->tetrominoGrid[i][j] % BLOCK_TYPES;
                al_draw_bitmap(sprites->blocks[game->level % LEVEL_STYLES][blockCode], j * BLOCK_W + GAME_OFFSET_X, i * BLOCK_H + GAME_OFFSET_Y, 0);
            }
        }
    }
}
static void allegroDrawActiveTetromino(const Game* game, SPRITES* sprites)
{
    int blockCode = 0;
    // Draw active tetromino
    switch (game->activeTetromino.shapeIndex)
    {
    case I:
    case O:
    case T:
        blockCode = WHITE;
        break;
    case L:
    case Z:
        blockCode = LIGHT;
        break;
    case J:
    case S:
        blockCode = DARK;
        break;
    default:
        break;
    }

    int i;
    int j;
    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j] != 0)
            {
                al_draw_bitmap(sprites->blocks[game->level % LEVEL_STYLES][blockCode], (game->activeTetromino.x + j) * BLOCK_W + GAME_OFFSET_X, (game->activeTetromino.y + i) * BLOCK_H + GAME_OFFSET_Y, 0);
            }
        }
    }
}

// Draws game level
static void allegroDrawLevel(const Game* game)
{
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        208, 160,
        0,
        "%02d",
        game->level
    );
}

// Draws the next tetromino to be played
static void allegroDrawNextTetromino(const Game* game, SPRITES* sprites)
{
    int blockCode = 0;
    int offsetX = 0;
    int offsetY = 0;

    switch (game->nextTetromino.shapeIndex)
    {
    case I:
        blockCode = WHITE;
        offsetX = 0;
        offsetY = BLOCK_H / 2;
        break;
    case O:
        blockCode = WHITE;
        offsetX = BLOCK_W;
        offsetY = BLOCK_H;
        break;
    case T:
        blockCode = WHITE;
        offsetX = BLOCK_W / 2;
        offsetY = BLOCK_H;
        break;
    case L:
    case Z:
        blockCode = LIGHT;
        offsetX = BLOCK_W / 2;
        offsetY = BLOCK_H;
        break;

    case J:
    case S:
        blockCode = DARK;
        offsetX = BLOCK_W / 2;
        offsetY = BLOCK_H;
        break;
    default:
        break;
    }

    int i;
    int j;
    for (i = 0; i < TETROMINO_H; i++)
    {
        for (j = 0; j < TETROMINO_W; j++)
        {
            if (game->nextTetromino.shape[i][j] != 0)
            {
                al_draw_bitmap(
                    sprites->blocks[game->level % LEVEL_STYLES][blockCode],
                    (game->nextTetromino.x + j) * BLOCK_W + NEXT_OFFSET_X + offsetX,
                    (game->nextTetromino.y + i) * BLOCK_H + NEXT_OFFSET_Y + offsetY,
                    0);
            }
        }
    }
}
static void allegroDrawGameOver(long score)
{
    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba_f(0, 0, 0, 0.8));
    al_draw_text(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2, BUFFER_H / 4,
        ALLEGRO_ALIGN_CENTER,
        "G A M E  O V E R"
    );
    al_draw_text(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2, 3 * BUFFER_H / 4,
        ALLEGRO_ALIGN_CENTER,
        "PRESS SPACE TO CONTINUE"
    );
    al_draw_text(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2, BUFFER_H / 2 + 5,
        ALLEGRO_ALIGN_CENTER,
        "POINTS"
    );
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2, BUFFER_H / 2 - 15,
        ALLEGRO_ALIGN_CENTER,
        "%06ld",
        score
    );
}
static void allegroDrawPause(void)
{
    al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba_f(0, 0, 0, 0.9));
    al_draw_text(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2, BUFFER_H / 4,
        ALLEGRO_ALIGN_CENTER,
        "G A M E  P A U S E D"
    );

    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    al_draw_filled_triangle(9 + 98, 0+ 111, 0+ 98, 4.5 + 111, 9+ 98, 9+ 111, white);
    al_draw_text(
        allegro->font,
        white,
        98 + 9 + 6, 111 + 1,
        0,
        "MENU"
    );

    al_draw_filled_triangle(0 + 98, 9 + 111 + 16, 4.5 + 98, 0 + 111 + 16, 9 + 98, 9 + 111 + 16, white);
    al_draw_text(
        allegro->font,
        white,
        98 + 9 + 6, 111 + 1 + 16,
        0,
        "RESTART"
    );

    al_draw_filled_triangle(0 + 98, 0 + 111 + 16 + 16, 4.5 + 98, 9 + 111 + 16 + 16, 9 + 98, 0 + 111 + 16 + 16, white);
    al_draw_text(
        allegro->font,
        white,
        98 + 9 + 6, 111 + 1 + 16 + 16,
        0,
        "RESUME"
    );

    al_draw_filled_triangle(0 + 98, 0 + 111 + 16 + 16 + 16, 0 + 98, 9 + 111 + 16 + 16 + 16, 9 + 98, 4.5 + 111 + 16 + 16 + 16, white);
    al_draw_text(
        allegro->font,
        white,
        98 + 9 + 6, 111 + 1 + 16 + 16 + 16,
        0,
        "SAVE"
    );
}

// Draws lines and tetromino statistics
static void allegroDrawStatistics(const Game* game, SPRITES* sprites)
{
    int index;
    int statisticOffsetX = 55;
    int statisticOffsetY = 80;

    for (index = 0; index < NUM_SHAPES; index++)
    {
        int blockCode = 0;
        int offsetX = 18;
        int offsetY = 76;
        switch (index)
        {
        case I:
            blockCode = WHITE;
            offsetY += index * BLOCK_H * 2 + index * 2 - BLOCK_H / 2;
            break;
        case O:
            blockCode = WHITE;
            offsetX += BLOCK_W;
            offsetY += index * BLOCK_H * 2 + index * 2;
            break;
        case T:
            blockCode = WHITE;
            offsetX += BLOCK_W / 2;
            offsetY += index * BLOCK_H * 2 + index * 2;
            break;
        case L:
        case Z:
            blockCode = LIGHT;
            offsetX += BLOCK_W / 2;
            offsetY += index * BLOCK_H * 2 + index * 2;
            break;
        case J:
        case S:
            blockCode = DARK;
            offsetX += BLOCK_W / 2;
            offsetY += index * BLOCK_H * 2 + index * 2;
            break;
        default:
            break;
        }

        int i;
        int j;
        for (i = 0; i < TETROMINO_H; i++)
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                if (tetrominoShapes[index][0][i][j] != 0)
                {
                    al_draw_bitmap(
                    		sprites->blocks[game->level % LEVEL_STYLES][blockCode], // @suppress("Field cannot be resolved")
                        j * BLOCK_W + offsetX, i * BLOCK_H + offsetY,
                        0);
                }
            }
        }

        // Draws completed lines
        al_draw_textf(
            allegro->font,
            al_map_rgb_f(1, 1, 1),
            statisticOffsetX, statisticOffsetY + 18 * index,
            0,
            "%03d",
            game->statistics[index]
        );
    }
}

static void allegroDrawHighScore(long score, int scoreIndex)
{
    const char* scoreString = "NEW HIGHSCORE #  !!!";
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2, BUFFER_H / 2,
        ALLEGRO_ALIGN_CENTER,
        "%s",
        scoreString
    );
}
//DRAW LEADERBOARD


static void initializeAllegro(Game* game, SPRITES* sprites)
{
    // Initialize Allegro
    checkInitialization(al_init(), "Allegro");

    // Initialize display
    allegroInitializeDisplay();

    // Initialize sprites
    allegroInitializeSprites(sprites);

    // Initialize primitives addon
    checkInitialization(al_init_primitives_addon(), "primitives");

    // Initialize fonts
    allegroInitializeFonts();

    // Initialize sound
    allegroInitializeSound();

    // Initialize keyboard
    checkInitialization(al_install_keyboard(), "keyboard");

    // Initialize timer
    allegroInitializeTimer();

    // Create event queue
    allegroInitializeEventQueue();

    // Gets the top score
    allegroGetTopScore(game);


}

static void allegroInitializeDisplay(void)
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    allegro->display = al_create_display(DISPLAY_W, DISPLAY_H);
    checkInitialization(allegro->display, "display");

    allegro->buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    checkInitialization(allegro->buffer, "bitmap buffer");

    // Set window title
    al_set_window_title(allegro->display, "Tetris");
}

// Initializes image addon and grabs all sprites
static void allegroInitializeSprites(SPRITES* sprites)
{
    checkInitialization(al_init_image_addon(), "image");

    sprites->_sheet = al_load_bitmap("spritesheet.png");
    checkInitialization(sprites->_sheet, "spritesheet");

    int i, j;
    for (i = 0; i < LEVEL_STYLES; i++)
    {
        for (j = 0; j < BLOCK_TYPES; j++)
        {
            sprites->blocks[i][j] = allegroGrabSprite(BLOCK_W * j, i * BLOCK_H, BLOCK_W, BLOCK_H, sprites);
        }
    }

    sprites->hud = allegroGrabSprite(HUD_OFFSET_X, 0, BUFFER_W, BUFFER_H, sprites);

    sprites->menu = allegroGrabSprite(MENU_OFFSET_x, 0, BUFFER_W, BUFFER_H, sprites);
}

// Initializes font addon and creates font
static void allegroInitializeFonts(void)
{
    checkInitialization(al_init_font_addon(), "font addon");
    allegro->font = al_create_builtin_font();
    checkInitialization(allegro->font, "font");

    allegro->score_display = 0;
}

// Initializes audio addon and reserves samples
static void allegroInitializeSound(void)
{
    checkInitialization(al_install_audio(), "audio");
    checkInitialization(al_init_acodec_addon(), "audio codecs");
    checkInitialization(al_reserve_samples(16), "reserve samples");

    ALLEGRO_SAMPLE* burnSFX = al_load_sample("burn.wav");
    checkInitialization(burnSFX, "burn");
    ALLEGRO_SAMPLE* tetrisSFX = al_load_sample("tetris.wav");
    checkInitialization(tetrisSFX, "tetris");
    ALLEGRO_SAMPLE* moveSidewaysSFX = al_load_sample("moveSideways.wav");
    checkInitialization(moveSidewaysSFX, "move sideways");
    ALLEGRO_SAMPLE* rotateSFX = al_load_sample("rotate.wav");
    checkInitialization(rotateSFX, "rotate");
    ALLEGRO_SAMPLE* fixSFX = al_load_sample("fix.wav");
    checkInitialization(fixSFX, "fix");
    ALLEGRO_SAMPLE* gameOverSFX = al_load_sample("gameOver.wav");
    checkInitialization(gameOverSFX, "game over");
    ALLEGRO_SAMPLE* victorySFX = al_load_sample("victory.wav");
    checkInitialization(victorySFX, "victory");

    allegro->SFX[BURN] = burnSFX;
    allegro->SFX[TETRIS] = tetrisSFX;
    allegro->SFX[MOVE_SIDEWAYS] = moveSidewaysSFX;
    allegro->SFX[ROTATE] = rotateSFX;
    allegro->SFX[FIX] = fixSFX;
    allegro->SFX[GAME_OVER] = gameOverSFX;
    allegro->SFX[VICTORY] = victorySFX;

    allegro->music = al_load_audio_stream("music1.wav", 2, 2048);
    checkInitialization(allegro->music, "music");
    al_set_audio_stream_playmode(allegro->music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(allegro->music, 0.3);
    al_attach_audio_stream_to_mixer(allegro->music, al_get_default_mixer());
}

// Initializes event queue and registers event sources
static void allegroInitializeEventQueue(void)
{
    allegro->eventQueue = al_create_event_queue();
    checkInitialization(allegro->eventQueue, "event queue");

    // Register display and timer event sources in the event queue
    al_register_event_source(allegro->eventQueue, al_get_display_event_source(allegro->display));
    al_register_event_source(allegro->eventQueue, al_get_timer_event_source(allegro->timer));
    al_register_event_source(allegro->eventQueue, al_get_timer_event_source(allegro->gametimer));
    al_register_event_source(allegro->eventQueue, al_get_keyboard_event_source());
}

// Initializes timer
static void allegroInitializeTimer(void)
{
    allegro->timer = al_create_timer(1.0 / FPS);
    checkInitialization(allegro->timer, "timer");

    allegro->gametimer = al_create_timer(1.0 / 1);
    checkInitialization(allegro->gametimer, "gametimer");
    // Start timer
    al_start_timer(allegro->timer);
}

// Grabs a sprite from the spritesheet
static ALLEGRO_BITMAP* allegroGrabSprite(int x, int y, int w, int h, SPRITES* sprites)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites->_sheet, x, y, w, h);
    checkInitialization(sprite, "sprite grab");
    return sprite;
}

static void destroyAllegro(SPRITES* sprites)
{
    // Destroy event queue
    al_destroy_event_queue(allegro->eventQueue);

    // Destroy timer
    al_destroy_timer(allegro->timer);
    al_destroy_timer(allegro->gametimer);

    // Destroy sound
    allegroDestroySound();


    // Destroy sprites
    allegroDestroySprites(sprites);

    // Destroys font
    al_destroy_font(allegro->font);

    // Destroy display
    allegroDestroyDisplay();
}
// Destroys all samples and music
static void allegroDestroySound(void)
{
    int i;
    for (i = 0; allegro->SFX[i] != NULL; i++)
    {
        al_destroy_sample(allegro->SFX[i]);
    }

    al_destroy_audio_stream(allegro->music);
}

// Destroys display and buffer
static void allegroDestroyDisplay(void)
{
    al_destroy_display(allegro->display);
    al_destroy_bitmap(allegro->buffer);
}

// Destroys all sprite bitmaps
static void allegroDestroySprites(SPRITES* sprites)
{
    for (int i = 0; i < LEVEL_STYLES; i++)
    {
        for (int j = 0; j < BLOCK_TYPES; j++)
        {
            al_destroy_bitmap(sprites->blocks[i][j]);
        }
    }
    al_destroy_bitmap(sprites->menu);
    al_destroy_bitmap(sprites->hud);
    al_destroy_bitmap(sprites->_sheet);
}

// Ensures correct initialization of allegro elements
static void checkInitialization(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);

    exit(1);
}

#else
#endif

