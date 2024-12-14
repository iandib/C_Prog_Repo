/*
 * th2_display_sound.c
 *
 *  Created on: Nov 25, 2024
 *      Author: Luchelli, Dib, Moschini, Caorsi
 */
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "th2_display_sound.h"
#include "th1_gamelogic.h"
#include <time.h>
#include <string.h>
#include <unistd.h>

#ifdef PC
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#else
#include "../libs/joydisp/disdrv.h"  // Archivo de cabecera del display
#include "../libs/joydisp/joydrv.h"   // Archivo de cabecera del joystick
#include "../libs/audio/SDL2/src/audio.h"   // Archivo de cabecera del joystick
#include <SDL2/SDL.h>
#endif

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

#define MENU_BLINK_ON_DELAY 50
#define MENU_BLINK_OFF_DELAY -20

// --- score ---
#define MAX_SCORE 999999

#ifndef PC

#define GAME "music1.wav"
#define LINE "burn.wav"
#define LOSE "gameOver.wav"
#define MOVE "moveSideways.wav"
#define ROT "rotate.wav"
#define LEVEL "tetris.wav"
#define FIX "fix.wav"

#define INITIAL_FALL_TIME 40
#define JOYSTICK_DELAY 50

char * raspySoundArray [10] = {0};
char** raspySounds = &raspySoundArray;

#endif

/*******************************************************************************
 * TYPEDEFs, ENUMs AND PRIVATE PROTOTYPES
 ******************************************************************************/

#ifdef PC
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
    ALLEGRO_TIMER* displayRedrawTimer;
    ALLEGRO_TIMER* fallingTimer;

    // score
    long topScore;
    int scoreIndex;

} ALLEGRO_ELEMENTS;

typedef struct keys
{
	short int delay_key_down;
	bool key_down_pressed;

	short int delay_key_left;
	bool key_left_pressed;

	short int delay_key_up;
	bool key_up_pressed;

	short int delay_key_right;
	bool key_right_pressed;
} keys;

enum blockTypes
{
    WHITE = 0,
    LIGHT,
    DARK,
    STRIPES
};


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
static void save_game(Game* game);
static void press_key_delay(keys* pressed_keys, Game* game);

static ALLEGRO_ELEMENTS allegroElements = { 0 };
static ALLEGRO_ELEMENTS* allegro = &allegroElements;

#else

static void draw_board(Game* game);
static void showNext(Game* game);
static void showLevel(Game* game);
static void initializeRaspy();
static void draw_tetromino(Game* game);

static void raspyShowScore(int score, joyinfo_t* coord);
static void raspyMenu(int[16][16]);

extern int digitMatrices[10][8][6];
extern int menuMatrices[4][8][8];
extern int menuViews[4][16][16];

static bool movedLeft(joyinfo_t* coord);
static bool movedRight(joyinfo_t* coord);
static bool movedDown(joyinfo_t* coord);
static bool movedUp(joyinfo_t* coord);
static bool switch_pressed(joyinfo_t* coord);

#endif

static int compare(const void* p1, const void* p2);

void initialize_leaderboard(Game* game);
static void update_leaderboard(Game* game);
void recover_game(Game* game);
void * th2_display_sound(void* game);
void playSoundIndex(int soundIndex);

extern int tetrominoShapes[NUM_SHAPES][TETROMINO_R][TETROMINO_H][TETROMINO_W];
extern sem_t s;

typedef struct
{
	short int delay_joy_down;
	short int delay_joy_left;
	short int delay_joy_right;
	short int delay_joy_up;
	short int delay_joy_switch;
} delay_joy_t;

void * th2_display_sound(void* gamep)
{
	Game* game = gamep;
#ifdef PC
	bool pressed = false;
	SPRITES sprites;
	keys pressed_keys = {0, false, 0, false, 0, false, 0, false};
	initializeAllegro(game, &sprites);
	while(!game->quit)
	{
        if(game->hasLevelChanged)
        {
            al_set_timer_speed( allegro->fallingTimer, 1.0 / ((double)game->level*3/4) );
            game->hasLevelChanged = false;
        }
		ALLEGRO_EVENT event;
		al_wait_for_event(allegro->eventQueue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			if (event.timer.source == allegro->displayRedrawTimer)
			{
				allegroUpdateHud(game);
				game->redraw = true;
			}
			else if(event.timer.source == allegro->fallingTimer)
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
							pressed_keys.key_down_pressed = false;
							pressed_keys.key_left_pressed = false;
							pressed_keys.key_right_pressed = false;
							pressed_keys.key_up_pressed = false;
							al_start_timer(allegro->fallingTimer);
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
							al_resume_timer(allegro->fallingTimer);
							break;

						case ALLEGRO_KEY_UP:
							game->restart = true;
							//game->pause = false;
							//game->restart = true;
							//initializeGame(game);
							//generateNewTetromino(game);
							//remove("saving.txt");
							//al_start_timer(allegro->fallingTimer);
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
							//game->menu = true;
							//game->gameOver = false;
							game->restart = true;
							al_stop_timer(allegro->fallingTimer);
							sem_post(&s);
							//initializeGame(game);
							//generateNewTetromino(game);
							break;
					}
				}
				else
				{
					switch(event.keyboard.keycode)
					{
						case ALLEGRO_KEY_DOWN:
							game->activeTetromino.move_down++;
							pressed_keys.delay_key_down = KEY_DELAY;
							pressed_keys.key_down_pressed = true;
							al_stop_timer(allegro->fallingTimer);
						break;

						case ALLEGRO_KEY_UP:
							game->activeTetromino.rotate_++;
							pressed_keys.delay_key_up = KEY_DELAY;
							pressed_keys.key_up_pressed = true;
						break;

						case ALLEGRO_KEY_LEFT:
							game->activeTetromino.move_left++;
							pressed_keys.delay_key_left = KEY_DELAY;
							pressed_keys.key_left_pressed = true;
							break;

						case ALLEGRO_KEY_RIGHT:
							game->activeTetromino.move_right++;
							pressed_keys.delay_key_right = KEY_DELAY;
							pressed_keys.key_right_pressed = true;
							break;

						case ALLEGRO_KEY_ESCAPE:
							game->pause = true;
							al_stop_timer(allegro->fallingTimer);
							break;
						case ALLEGRO_KEY_SPACE: game->activeTetromino.move_down += DISPLAY_H; break;

						default: break;
					}
				}
			}
		}
		else if(event.type == ALLEGRO_EVENT_KEY_UP)
		{
			if(!game->menu && !game->pause && !game->gameOver)
			{
				switch(event.keyboard.keycode)
				{
					case ALLEGRO_KEY_DOWN: pressed_keys.key_down_pressed = false; al_resume_timer(allegro->fallingTimer); break;

					case ALLEGRO_KEY_UP: pressed_keys.key_up_pressed = false; break;

					case ALLEGRO_KEY_LEFT: pressed_keys.key_left_pressed = false; break;

					case ALLEGRO_KEY_RIGHT: pressed_keys.key_right_pressed = false; break;

					default: break;
				}
			}
		}
		if(!game->menu && !game->gameOver && !game->pause)
		{
			press_key_delay(&pressed_keys, game);
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
    double raspyFallTime = INITIAL_FALL_TIME;
    delay_joy_t delay_joy = {JOYSTICK_DELAY, JOYSTICK_DELAY, JOYSTICK_DELAY, JOYSTICK_DELAY, JOYSTICK_DELAY};
    joyinfo_t coord;
    initializeRaspy();
	raspyMenu(menuViews[TITLE]);
	SDL_Delay(6000);

    while(!game->quit)
    {
	    disp_clear();
    	coord = joy_read();
    	if(game->menu)
    	{
			pauseAudio();
			switch(game->menu)
			{
				/* The number in case corresponds to the index in menuViews. There an offset of 1 because
				game->menu needs to be true for the game to stay in the menu. */
				case PLAY:				
					raspyMenu(menuViews[PLAY]);
					break;
				case EXIT:					
					raspyMenu(menuViews[EXIT]);
					break;
				case INSTRUCTION_1:
					raspyMenu(menuViews[INSTRUCTION_1]);
					break;
				case INSTRUCTION_2:
					raspyMenu(menuViews[INSTRUCTION_2]);
					break;
				default: break;
			}
			if(movedRight(&coord) && !delay_joy.delay_joy_right)
			{
			   if(game->menu <= NUMBER_OF_SLIDES)
			   {
					game->menu++;
					delay_joy.delay_joy_right = JOYSTICK_DELAY;
			   }
			}
		
			if(movedLeft(&coord) && !delay_joy.delay_joy_left)
			{
			   if(game->menu > 1)
			   {
					game->menu--;
					delay_joy.delay_joy_left = JOYSTICK_DELAY;
			   }
			}
			if(switch_pressed(&coord) && !delay_joy.delay_joy_switch)
			{
				if(game->menu == PLAY)
				{
                    unpauseAudio();
                    game->menu = false;
                    game->gameOver = false;
                    delay_joy.delay_joy_switch = JOYSTICK_DELAY;
                    delay_joy.delay_joy_up = 0;
                    delay_joy.delay_joy_down = 0;
                    delay_joy.delay_joy_left = 0;
                    delay_joy.delay_joy_right = 0;
                    sem_post(&s);
                
				}
				else if(game->menu == EXIT)
				{
					game->quit = true;
					sem_post(&s);
				}
			}
    	}
    	else if(game->pause)
    	{
			if (movedLeft(&coord))
			{
				unpauseAudio();
				sem_post(&s);
				game->pause = false;
			}
			else if (movedRight(&coord))
			{
				unpauseAudio();
				game->pause = false;
				game->restart = true;
				sem_post(&s);
			}
			else if (movedUp(&coord))
			{
				pauseAudio();
				game->menu = true;
				game->pause = false;
			}
    	}
    	else if(game->gameOver)
        {
            while (!movedRight(&coord))
            {
            	coord = joy_read();
                raspyShowScore(game->score, &coord);
            }
            initializeGame(game);
            sem_post(&s);
        }
    	else
    	{
			draw_board(game);
			showLevel(game);
			showNext(game);
			draw_tetromino(game);
    		if(raspyFallTime > 0)
			{
				raspyFallTime -= (1 + game->level / 3 );
			}
			else
			{
				game->activeTetromino.move_down++;
				raspyFallTime = INITIAL_FALL_TIME;
			}

			if(movedUp(&coord) && !delay_joy.delay_joy_up)
			{
				game->activeTetromino.rotate_++;
				delay_joy.delay_joy_up = 10;
			}
			if(movedDown(&coord) && !delay_joy.delay_joy_down)
			{
				game->activeTetromino.move_down++;
				delay_joy.delay_joy_down = 10;
			}
			if(movedLeft(&coord) && !delay_joy.delay_joy_left)
			{
				game->activeTetromino.move_left++;
				delay_joy.delay_joy_left = 10;
			}
			if(movedRight(&coord) && !delay_joy.delay_joy_right)
			{
				game->activeTetromino.move_right++;
				delay_joy.delay_joy_right = 10;
			}
			if(switch_pressed(&coord) && !delay_joy.delay_joy_switch)
			{
				disp_clear();
				game->pause = true;
				delay_joy.delay_joy_switch = JOYSTICK_DELAY;
			}
    	}
    	delay_joy.delay_joy_down > 0 ? delay_joy.delay_joy_down-- : true;
    	delay_joy.delay_joy_left > 0 ? delay_joy.delay_joy_left-- : true;
    	delay_joy.delay_joy_right > 0 ? delay_joy.delay_joy_right-- : true;
    	delay_joy.delay_joy_up > 0 ? delay_joy.delay_joy_up-- : true;
    	delay_joy.delay_joy_switch > 0 ? delay_joy.delay_joy_switch-- : true;
    }
    endAudio();
	disp_clear();
	disp_update();
    pthread_exit(NULL);
#endif
}
void playSoundIndex(int soundIndex)
{
	#ifdef PC
	al_play_sample(allegro->SFX[soundIndex], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	#else
	playSound(raspySounds[soundIndex], SDL_MIX_MAXVOLUME);
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

static void allegroGetTopScore(Game* game)
{
    if (game->leaderboard[0].score <= MAX_SCORE)
    {
        allegro->topScore = game->leaderboard[0].score;
    }
    else
    {
        allegro->topScore = MAX_SCORE;
    }
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
    	al_draw_bitmap(sprites->menu, 0, 0, 0); 
	
	static int menu_blink_delay = MENU_BLINK_ON_DELAY;
   	
	menu_blink_delay--;
	// Draws text
	if(menu_blink_delay > 0)
	{
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
	menu_blink_delay < MENU_BLINK_OFF_DELAY  ? menu_blink_delay = MENU_BLINK_ON_DELAY : 1;
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
static void allegroDrawActiveTetromino(const Game* game, SPRITES* sprites)						// Draws active tetromino
{
    int blockCode = 0;
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

static void allegroDrawLevel(const Game* game)											// Draws game level on the game screen
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

static void allegroDrawNextTetromino(const Game* game, SPRITES* sprites)					// Draws the next tetromino to be played
{
    int blockCode = 0;
    int offsetX = 0;
    int offsetY = 0;

    switch (game->nextTetromino.shapeIndex)														//Positions the next tetromino shape on the corrent spot of the game screen and gives it color
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
        for (j = 0; j < TETROMINO_W; j++)										//Draws the next tetromino shape on the right
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
static void allegroDrawGameOver(long score)								//Draws the game over screen with its options and points that were gathered during the game
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
static void allegroDrawPause(void)								//Draws the pause screen with its options
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

static void allegroDrawStatistics(const Game* game, SPRITES* sprites)						// Draws lines and tetromino statistics
{
    int index;
    int statisticOffsetX = 55;
    int statisticOffsetY = 80;

    for (index = 0; index < NUM_SHAPES; index++)							//For the statistics of every tetromino shape
    {
        int blockCode = 0;
        int offsetX = 18;
        int offsetY = 76;
        switch (index)														//Corrects the position of the statistics depending on the shape
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
        for (i = 0; i < TETROMINO_H; i++)									//Draws the corresponding tetromino shape
        {
            for (j = 0; j < TETROMINO_W; j++)
            {
                if (tetrominoShapes[index][0][i][j] != 0)
                {
                    al_draw_bitmap(
                    		sprites->blocks[game->level % LEVEL_STYLES][blockCode],
                        j * BLOCK_W + offsetX, i * BLOCK_H + offsetY,
                        0);
                }
            }
        }

        al_draw_textf(									       			 // Draws the number of tetrominos that were generated in the current game, sorting them by shape
            allegro->font,
            al_map_rgb_f(1, 1, 1),
            statisticOffsetX, statisticOffsetY + 18 * index,
            0,
            "%03d",
            game->statistics[index]
        );
    }
}

static void allegroDrawHighScore(long score, int scoreIndex)				//Draws highscore screen [TO BE CHECKED]
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


static void initializeAllegro(Game* game, SPRITES* sprites)								// Initialize Allegro
{
    checkInitialization(al_init(), "Allegro");

    // Initialize display
    allegroInitializeDisplay();

    // Initializes sprites
    allegroInitializeSprites(sprites);

    // Initializes primitives addon
    checkInitialization(al_init_primitives_addon(), "primitives");

    // Initializes fonts
    allegroInitializeFonts();

    // Initializes sound
    allegroInitializeSound();

    // Initializes keyboard
    checkInitialization(al_install_keyboard(), "keyboard");

    // Initializes timer
    allegroInitializeTimer();

    // Creates event queue
    allegroInitializeEventQueue();

    // Gets the top score
    allegroGetTopScore(game);
}

static void allegroInitializeDisplay(void)								//Creates the display, a buffer and sets window title
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    allegro->display = al_create_display(DISPLAY_W, DISPLAY_H);
    checkInitialization(allegro->display, "display");

    allegro->buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    checkInitialization(allegro->buffer, "bitmap buffer");

    al_set_window_title(allegro->display, "Tetris");
}

static void allegroInitializeSprites(SPRITES* sprites)								// Initializes image addon and grabs all of the sprites
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

static void allegroInitializeFonts(void)											// Initializes font addon and creates builtin font as well as sets the displayed score in 0
{
    checkInitialization(al_init_font_addon(), "font addon");
    allegro->font = al_create_builtin_font();
    checkInitialization(allegro->font, "font");
    allegro->score_display = 0;
}

static void allegroInitializeSound(void)											// Initializes audio addon and reserves samples
{
    checkInitialization(al_install_audio(), "audio");								//Initializes audio, acodec addon and reserves samples.
    checkInitialization(al_init_acodec_addon(), "audio codecs");
    checkInitialization(al_reserve_samples(16), "reserve samples");

    ALLEGRO_SAMPLE* burnSFX = al_load_sample("burn.wav");							//Initializes all the samples, one by one.
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

    allegro->SFX[BURN] = burnSFX;													//Loads the samples in the proper field of the allegro struct
    allegro->SFX[TETRIS] = tetrisSFX;
    allegro->SFX[MOVE_SIDEWAYS] = moveSidewaysSFX;
    allegro->SFX[ROTATE] = rotateSFX;
    allegro->SFX[FIX] = fixSFX;
    allegro->SFX[GAME_OVER] = gameOverSFX;
    allegro->SFX[VICTORY] = victorySFX;

    allegro->music = al_load_audio_stream("music1.wav", 2, 2048);					//Loads the backround music in the audio stream, plays it in loop, and attaches it to the default mixer
    checkInitialization(allegro->music, "music");
    al_set_audio_stream_playmode(allegro->music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(allegro->music, 0.3);
    al_attach_audio_stream_to_mixer(allegro->music, al_get_default_mixer());
}

static void allegroInitializeEventQueue(void)														// Initializes event queue and registers event sources
{
    allegro->eventQueue = al_create_event_queue();
    checkInitialization(allegro->eventQueue, "event queue");

    al_register_event_source(allegro->eventQueue, al_get_display_event_source(allegro->display));			    // Registers display and timer event as sources in the event queue
    al_register_event_source(allegro->eventQueue, al_get_timer_event_source(allegro->displayRedrawTimer));
    al_register_event_source(allegro->eventQueue, al_get_timer_event_source(allegro->fallingTimer));
    al_register_event_source(allegro->eventQueue, al_get_keyboard_event_source());
}

static void allegroInitializeTimer(void)													// Initializes the timers
{
    allegro->displayRedrawTimer = al_create_timer(1.0 / FPS  );					//Display redraw timer
    checkInitialization(allegro->displayRedrawTimer, "displayRedrawTimer");

    allegro->fallingTimer = al_create_timer( 1.0 / 1.0); //CAPAZ ES MUY ALTO		//Falling timer
    checkInitialization(allegro->fallingTimer, "fallingTimer");
    // Start timer
    al_start_timer(allegro->displayRedrawTimer);
}

static ALLEGRO_BITMAP* allegroGrabSprite(int x, int y, int w, int h, SPRITES* sprites)				// Grabs a sprite from the spritesheet
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites->_sheet, x, y, w, h);
    checkInitialization(sprite, "sprite grab");
    return sprite;
}

static void destroyAllegro(SPRITES* sprites)						//Destroys allegro elements
{
    // Destroys event queue
    al_destroy_event_queue(allegro->eventQueue);

    // Destroys timer
    al_destroy_timer(allegro->displayRedrawTimer);
    al_destroy_timer(allegro->fallingTimer);

    // Destroys sound
    allegroDestroySound();


    // Destroys sprites
    allegroDestroySprites(sprites);

    // Destroys font
    al_destroy_font(allegro->font);

    // Destroys display
    allegroDestroyDisplay();
}

static void allegroDestroySound(void)										// Destroys all samples and music
{
    int i;
    for (i = 0; allegro->SFX[i] != NULL; i++)
    {
        al_destroy_sample(allegro->SFX[i]);
    }
    al_destroy_audio_stream(allegro->music);
}

static void allegroDestroyDisplay(void)										// Destroys display and buffer
{
    al_destroy_display(allegro->display);
    al_destroy_bitmap(allegro->buffer);
}

static void allegroDestroySprites(SPRITES* sprites)							// Destroys all sprite bitmaps
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

static void checkInitialization(bool test, const char* description)					// Ensures correct initialization of allegro elements
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}
static void press_key_delay(keys* pressed_keys, Game* game)
{
		if(pressed_keys->key_down_pressed)
		{
			if(pressed_keys->delay_key_down < 0)
			{
				pressed_keys->delay_key_down++;
			}
			else
			{
				game->activeTetromino.move_down++;
				pressed_keys->delay_key_down = KEY_DELAY;
			}
		}
		if(pressed_keys->key_up_pressed)
		{
			if(pressed_keys->delay_key_up < 0)
			{
				pressed_keys->delay_key_up++;
			}
			else
			{
				game->activeTetromino.rotate_++;
				pressed_keys->delay_key_up = KEY_DELAY;
			}
		}
		if(pressed_keys->key_left_pressed)
		{
			if(pressed_keys->delay_key_left < 0)
			{
				pressed_keys->delay_key_left++;
			}
			else
			{
				game->activeTetromino.move_left++;
				pressed_keys->delay_key_left = KEY_DELAY;
			}
		}
		if(pressed_keys->key_right_pressed)
		{
			if(pressed_keys->delay_key_right < 0)
			{
				pressed_keys->delay_key_right++;
			}
			else
			{
				game->activeTetromino.move_right++;
				pressed_keys->delay_key_right = KEY_DELAY;
			}
		}
}
#else

static void draw_board(Game* game)
 {
    dcoord_t coords;
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if (game->grid[i][j])
            {
                coords.x = j;
                coords.y = i;
                if (coords.x >= 0 && coords.x <= DISP_MAX_X && coords.y >= 0 && coords.y <= DISP_MAX_Y) {
                    disp_write(coords, D_ON);
                }
            }
            else
            {
                coords.x = j;
                coords.y = i;
                if (coords.x >= 0 && coords.x <= DISP_MAX_X && coords.y >= 0 && coords.y <= DISP_MAX_Y) {
                    disp_write(coords, D_OFF);
                }
            }
        }
    }
    disp_update();
}
//
static void draw_tetromino(Game* game)
{
    dcoord_t coords;
    for (int i = 0; i < TETROMINO_H; i++)
    {
        for (int j = 0; j < TETROMINO_W; j++)
        {
            if (game->activeTetromino.shape[i][j])
            {
                coords.x = j + game->activeTetromino.x;
                coords.y = i + game->activeTetromino.y;
                if (coords.x >= 0 && coords.x <= DISP_MAX_X && coords.y >= 0 && coords.y <= DISP_MAX_Y) {
                    disp_write(coords, D_ON);
                }
            }
        }
    }
    disp_update();
}

static void showNext(Game* game)
{
    dcoord_t coords;
    for (int i = 0; i < TETROMINO_H; i++)
    {
        for (int j = 0; j < TETROMINO_W; j++)
        {
            coords.x = j + 11;
            coords.y = i;
            disp_write(coords, D_OFF);
        }
    }
    for (int i = 0; i < TETROMINO_H; i++)
    {
        for (int j = 0; j < TETROMINO_W; j++)
        {
            if (game->nextTetromino.shape[i][j])
            {
                coords.x = j + 11;
                coords.y = i;
                disp_write(coords, D_ON);
            }
        }
    }
    disp_update();
}

static void showLevel(Game* game)
{
    dcoord_t coords;
    coords.x = 11 + game->level % 5; 
    coords.y = 10 + (int)game->level / 5;
	//10 and 11 are the coordinates in which the levels are drawn

    disp_write(coords, D_ON);
    disp_update();
}

/*static bool checkPasue()
{
    joyinfo_t coord = joy_read();
    if (coord.y > JOY_MAX_POS / 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}*/



static void initializeRaspy()
{
    joy_init();
    initAudio();

    raspySounds[BURN] = LINE;
    raspySounds[GAME_OVER] = LOSE;
    raspySounds[MOVE_SIDEWAYS] = MOVE;
    raspySounds[TETRIS] = LEVEL;
    raspySounds[ROTATE] = ROT;

    disp_init();
    disp_clear();
    disp_update();
    playMusic(GAME, SDL_MIX_MAXVOLUME / 2);
    srand(time(NULL));
}

static void raspyShowScore(int score, joyinfo_t* coord) {
    // Si el puntaje es 0, dibuja el dígito 0 y retorna
    if (score == 0) {
        // Desplaza el número de derecha a izquierda en el LED
        for (int offset_x = 16 - 6, offset_y = 8 - 4; offset_x >= -6; offset_x--) {
            // Borra el contenido actual del buffer
            disp_clear();

            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 6; k++) {
                    if (k + offset_x >= 0 && k + offset_x < 16) {
                        int x = k + offset_x;
                        int y = j + offset_y;

                        if (digitMatrices[0][j][k] == 1 && y >= 0 && y < 16) {
                            dcoord_t point = { x, y };
                            disp_write(point, D_ON);
                        }
                    }
                    if (movedRight(coord)) {
                        unpauseAudio();
                        disp_clear();
                        disp_update();
                        return;
                    }
                }
            }
            // Actualiza el display
            disp_update();

            // Espera un tiempo (ajusta según sea necesario)
            usleep(50000); // 50 milisegundos
        }
        return;
    }
    else
    {
		// Convierte el número en un array de dígitos
		int digits_array[6];
		for (int i = 5; i >= 0; i--) {
			digits_array[i] = score % 10;
			score /= 10;
		}

		// Encuentra el primer dígito no cero
		int firstNonZero = 0;
		while (firstNonZero < 6 && digits_array[firstNonZero] == 0) {
			firstNonZero++;
		}

		// Desplaza el número de derecha a izquierda en el LED
		for (int offset_x = 16 - 6, offset_y = 8 - 4; offset_x >= -6 - 30; offset_x--) {
			// Borra el contenido actual del buffer
			disp_clear();

			// Coloca los dígitos en el buffer con el desplazamiento actual
			for (int i = firstNonZero; i < 6; i++) {
				int x_start = (i - firstNonZero) * 6;

				for (int j = 0; j < 8; j++) {
					for (int k = 0; k < 6; k++) {
						if (x_start + k + offset_x >= 0 && x_start + k + offset_x < 16) {
							int x = x_start + k + offset_x;
							int y = j + offset_y;

							if (digitMatrices[digits_array[i]][j][k] == 1 && y >= 0 && y < 16) {
								dcoord_t point = { x, y };
								disp_write(point, D_ON);
							}
						}
						if (movedRight(coord)) {
							unpauseAudio();
							disp_clear();
							disp_update();
							return;
						}
					}
				}
			}

			// Actualiza el display
			disp_update();

			// Espera un tiempo (ajusta según sea necesario)
			SDL_Delay(50); // 50 milisegundos
		}
    }
}

static void raspyMenu(int menuScreen[16][16]) 
{
	dcoord_t coord;

    for (int i = 0; i < 16; ++i)
	 {
        for (int j = 0; j < 16; ++j) 
		{
            coord.x = j;
            coord.y = i;
            disp_write(coord, menuScreen[i][j]);
        }
    }
    // Actualizar la pantalla
    disp_update();
}
static bool movedLeft(joyinfo_t* coord)
{
    if (coord->x < JOY_MAX_NEG/2){
    	return true;
    }
    return false;
}
static bool movedRight(joyinfo_t* coord)
{
    if (coord->x > JOY_MAX_POS/2){
    	return true;
    }
    return false;
}

static bool movedDown(joyinfo_t* coord)
{
	if (coord->y < JOY_MAX_NEG/2){
		return true;
	}
	return false;
}
static bool movedUp(joyinfo_t* coord)
{
	if (coord->y > JOY_MAX_POS / 2)
	{
		return true;
	}
	return false;
}

static bool switch_pressed(joyinfo_t* coord)
{
	if (coord->sw == J_PRESS){
		return true;
	}
    return false;
}
#endif
