/*******************************************************************************
  @file     +allegro.c
  @brief    +Allegro constants and handling functions
  @author   +Helou, Luchelli, Segura
 ******************************************************************************/

 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/

#include "allegro.h"

#ifdef PC

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

// --- keyboard ---

#define KEY_SEEN     1
#define KEY_RELEASED 2

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



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

SPRITES sprites;

ALLEGRO_ELEMENTS allegroElements = { 0 };
ALLEGRO_ELEMENTS* allegro = &allegroElements;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// --- allegro ---
static void checkInitialization(bool test, const char* description);

// --- keyboard ---
static void allegroInitializeKeyboard();

// --- display ---
static void allegroInitializeDisplay();
static void allegroDestroyDisplay();

// --- sprites ---
static ALLEGRO_BITMAP* allegroGrabSprite(int x, int y, int w, int h);
static void allegroInitializeSprites();
static void allegroDestroySprites();

// --- hud ---
static void allegroInitializeHud();
static void allegroDestroyHud();

// --- sound ---
static void allegroInitializeSound();
static void allegroDestroySound();

// --- timer ---
static void allegroInitializeTimer();

// --- event queue ---
static void allegroInitializeEventQueue();

// --- drawing ---
static void allegroDrawNextTetromino(const Game* game);
static void allegroDrawLevel(const Game* game);
static void allegroDrawStatistics(const Game* game);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

// --- allegro ---

void initializeAllegro()
{
    // Initialize Allegro
    checkInitialization(al_init(), "Allegro");

    // Initialize display
    allegroInitializeDisplay();

    // Initialize sprites
    allegroInitializeSprites();

    // Initialize primitives addon
    checkInitialization(al_init_primitives_addon(), "primitives");

    // Initialize hud
    allegroInitializeHud();

    // Initialize sound
    allegroInitializeSound();

    // Initialize keyboard
    allegroInitializeKeyboard();

    // Seed random number generator
    srand(time(NULL));

    // Initialize timer
    allegroInitializeTimer();

    // Create event queue
    allegroInitializeEventQueue();

    // Gets the top score
    allegroGetTopScore();


}

void destroyAllegro()
{
    // Destroy event queue
    al_destroy_event_queue(allegro->eventQueue);

    // Destroy timer
    al_destroy_timer(allegro->timer);

    // Destroy sound
    allegroDestroySound();

    // Destroy hud
    allegroDestroyHud();

    // Destroy sprites
    allegroDestroySprites();

    // Destroy display
    allegroDestroyDisplay();
}


// --- keyboard ---

void allegroUpdateKeyboard(ALLEGRO_EVENT* event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            allegro->key[i] &= KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        allegro->key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;

    case ALLEGRO_EVENT_KEY_UP:
        allegro->key[event->keyboard.keycode] &= KEY_RELEASED;
        break;
    }
}


// --- display ---

void allegroDisplayPreDraw(ALLEGRO_BITMAP* buffer)
{
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void allegroDisplayPostDraw(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* buffer)
{
    al_set_target_backbuffer(display);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISPLAY_W, DISPLAY_H, 0);

    al_flip_display();
}


// --- hud ---

void allegroUpdateHud(Game* game)
{
    if (allegro->score_display <= MAX_SCORE)
    {
        // Resets score display
        if (allegro->score_display > game->score)
        {
            allegro->score_display = 0;
        }

        // Increases score display in steps
        for (long i = 5; i > 0; i--)
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

void allegroDrawHud(Game* game)
{
    // Draws framing
    al_draw_bitmap(sprites.hud, 0, 0, 0);

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
    allegroDrawNextTetromino(game);

    // Draws current level
    allegroDrawLevel(game);

    // Draws lines and tetromino statistics
    allegroDrawStatistics(game);
}


// --- drawing ---

void allegroDrawMenu()
{
    // Draws framing
    al_draw_bitmap(sprites.menu, 0, 0, 0);

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

void allegroDrawGrid(const Game* game)
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
                al_draw_bitmap(sprites.blocks[game->level % LEVEL_STYLES][blockCode], j * BLOCK_W + GAME_OFFSET_X, i * BLOCK_H + GAME_OFFSET_Y, 0);
            }
        }
    }
}

void allegroDrawActiveTetromino(const Game* game)
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
                al_draw_bitmap(sprites.blocks[game->level % LEVEL_STYLES][blockCode], (game->activeTetromino.x + j) * BLOCK_W + GAME_OFFSET_X, (game->activeTetromino.y + i) * BLOCK_H + GAME_OFFSET_Y, 0);
            }
        }
    }
}

void allegroDrawGameOver(long score)
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
        "POINTS"
    );
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2, 3 * BUFFER_H / 4 - 20,
        ALLEGRO_ALIGN_CENTER,
        "%06ld",
        score
    );
}

void allegroDrawHighScore(long score, int scoreIndex)
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
    al_draw_textf(
        allegro->font,
        al_map_rgb_f(1, 1, 1),
        BUFFER_W / 2 + 41, BUFFER_H / 2,
        0,
        "%02d",
        scoreIndex
    );
}

void allegroDrawPause()
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

    al_draw_filled_triangle(0 + 98, 9 + 111 + 16, 4.5 + 98, 0 + 111 + 16, 9 + 98, 9 + 111 + 16, white);;
    al_draw_text(
        allegro->font,
        white,
        98 + 9 + 6, 111 + 1 + 16,
        0,
        "RESTART"
    );

    al_draw_filled_triangle(0 + 98, 0 + 111 + 16 + 16, 4.5 + 98, 9 + 111 + 16 + 16, 9 + 98, 0 + 111 + 16 + 16, white);;
    al_draw_text(
        allegro->font,
        white,
        98 + 9 + 6, 111 + 1 + 16 + 16,
        0,
        "RESUME"
    );

}

void allegroUpdateColorMap(Game* game, int row, int col)
{
    switch (game->activeTetromino.shapeIndex)
    {
    case I:
    case O:
    case T:
        game->tetrominoGrid[row][col] = BLOCK_TYPES * (game->level % LEVEL_STYLES) + WHITE;
        break;
    case L:
    case Z:
        game->tetrominoGrid[row][col] = (BLOCK_TYPES * (game->level % LEVEL_STYLES)) + LIGHT;
        break;
    case J:
    case S:
        game->tetrominoGrid[row][col] = (BLOCK_TYPES * (game->level % LEVEL_STYLES)) + DARK;
        break;
    }
}


// --- sound ---

void allegroPlaySound(int soundIndex)
{
    al_play_sample(allegro->SFX[soundIndex], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}


// --- top score ---

void allegroGetTopScore()
{
    FILE* file = fopen("leaderboard.txt", "r"); // Open the file for reading
    long score;

    if (file == NULL)
    {
        printf("Error opening the leaderboard file.\n");
        exit(1);
    }

    if (fscanf(file, "%ld", &score) == EOF)
    {
		printf("Error reading the leaderboard file.\n");
		exit(1);

    }

    fclose(file);

    if (score <= MAX_SCORE)
        allegro->topScore = score;
    else
        allegro->topScore = MAX_SCORE;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

// Ensures correct initialization of allegro elements
static void checkInitialization(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);

    exit(1);
}


// --- keyboard ---

// Initializes keyboard addon
static void allegroInitializeKeyboard()
{
    checkInitialization(al_install_keyboard(), "keyboard");

    memset(allegro->key, 0, sizeof(allegro->key));
}


// --- display ---

// Initializes display and buffer
static void allegroInitializeDisplay()
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

// Destroys display and buffer
static void allegroDestroyDisplay()
{
    al_destroy_display(allegro->display);
    al_destroy_bitmap(allegro->buffer);
}


// --- sprites ---

// Grabs a sprite from the spritesheet
static ALLEGRO_BITMAP* allegroGrabSprite(int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
    checkInitialization(sprite, "sprite grab");
    return sprite;
}

// Initializes image addon and grabs all sprites
static void allegroInitializeSprites()
{
    checkInitialization(al_init_image_addon(), "image");

    sprites._sheet = al_load_bitmap("spritesheet.png");
    checkInitialization(sprites._sheet, "spritesheet");

    int i, j;
    for (i = 0; i < LEVEL_STYLES; i++)
    {
        for (j = 0; j < BLOCK_TYPES; j++)
        {
            sprites.blocks[i][j] = allegroGrabSprite(BLOCK_W * j, i * BLOCK_H, BLOCK_W, BLOCK_H);
        }
    }

    sprites.hud = allegroGrabSprite(HUD_OFFSET_X, 0, BUFFER_W, BUFFER_W);

    sprites.menu = allegroGrabSprite(MENU_OFFSET_x, 0, BUFFER_W, BUFFER_H);
}

// Destroys all sprite bitmaps
static void allegroDestroySprites()
{
    int i = 0, j = 0;
    for (i; i < LEVEL_STYLES; i++)
    {
        for (j; j < BLOCK_TYPES; j++)
        {
            al_destroy_bitmap(sprites.blocks[i][j]);
        }
    }

    al_destroy_bitmap(sprites._sheet);
}


// --- hud ---

// Initializes font addon and creates font
static void allegroInitializeHud()
{
    checkInitialization(al_init_font_addon(), "font addon");
    allegro->font = al_create_builtin_font();
    checkInitialization(allegro->font, "font");

    allegro->score_display = 0;
}

// Destroys font and hud bitmap
static void allegroDestroyHud()
{
    al_destroy_font(allegro->font);
    al_destroy_bitmap(sprites.hud);
}


// --- sound ---

// Initializes audio addon and reserves samples
static void allegroInitializeSound()
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

// Destroys all samples and music
static void allegroDestroySound()
{
    int i;
    for (i = 0; allegro->SFX[i] != NULL; i++)
    {
        al_destroy_sample(allegro->SFX[i]);
    }

    al_destroy_audio_stream(allegro->music);
}


// --- timer ---

// Initializes timer
static void allegroInitializeTimer()
{
    allegro->timer = al_create_timer(1.0 / FPS);
    checkInitialization(allegro->timer, "timer");

    // Start timer
    al_start_timer(allegro->timer);
}


// --- event queue ---

// Initializes event queue and registers event sources
static void allegroInitializeEventQueue()
{
    allegro->eventQueue = al_create_event_queue();
    checkInitialization(allegro->eventQueue, "event queue");

    // Register display, keyboard and timer event sources in the event queue
    al_register_event_source(allegro->eventQueue, al_get_display_event_source(allegro->display));
    al_register_event_source(allegro->eventQueue, al_get_keyboard_event_source());
    al_register_event_source(allegro->eventQueue, al_get_timer_event_source(allegro->timer));
}


// --- drawing ---

// Draws the next tetromino to be played
static void allegroDrawNextTetromino(const Game* game)
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
                    sprites.blocks[game->level % LEVEL_STYLES][blockCode], 
                    (game->nextTetromino.x + j) * BLOCK_W + NEXT_OFFSET_X + offsetX, 
                    (game->nextTetromino.y + i) * BLOCK_H + NEXT_OFFSET_Y + offsetY, 
                    0);
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

// Draws lines and tetromino statistics
static void allegroDrawStatistics(const Game* game)
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
                        sprites.blocks[game->level % LEVEL_STYLES][blockCode], 
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

#endif //PC