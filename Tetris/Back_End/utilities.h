/* *****************************************************************
    *                    HEADER CONFIGURATION                     *
   ***************************************************************** */

// We make sure the header is only included once 
#ifndef UTILITIES_h
#define UTILITIES_h

/* --------------------- NECESSARY LIBRARIES --------------------- */

// Standard boolean data types library
#include <stdbool.h>

// Standard thread management library
#include <pthread.h>

/* ---------------- MACROS & CONSTANTS (UNIVERSAL) ---------------- */

// Number of unique tetromino shapes in the game
#define NUM_SHAPES 7

// Width of a tetromino in cells
#define TETROMINO_W 4

// Height of a tetromino in cells
#define TETROMINO_H 4

// Number of possible rotations for a tetromino
#define TETROMINO_R 4

// Width of the game grid in cells
#define GRID_WIDTH 10

/* ------------------- MACROS & CONSTANTS (PC) ------------------- */

// The following constants are only used for the PC version of the game
#ifdef PC

// Delay (in frames) before a piece is fixed in place after hitting the bottom or another block
#define FIX_DELAY 10

// Frames per second for the game loop
#define FPS 60

// Delay (in milliseconds) between key inputs
#define KEY_DELAY -15

// Height of the game grid in cells (Raspberry Pi version)
#define GRID_HEIGHT 20

/* ---------------- MACROS & CONSTANTS (RASPBERRY) ---------------- */

// The following constants are only used for the Raspberry Pi version of the game
#else

// Delay (in frames) before a piece is fixed in place after hitting the bottom or another block
#define FIX_DELAY 5

// Height of the game grid in cells for the PC version
#define GRID_HEIGHT 16

// Delay (in frames) before processing joystick input
#define JOY_ON_DELAY 6

// Delay (in frames) before clearing joystick coordinates
#define CLEAR_JOY_COORD_DELAY 3

#define NUMBER_OF_SLIDES 5

#endif // PC

/* ---------------------- STRUCTURES & ENUMS ---------------------- */

// Enumeration for the indices of tetromino shapes
enum tetrominoShapeIndex
{
    L = 0,  // L-shaped tetromino
    J,      // J-shaped tetromino
    I,      // I-shaped tetromino
    O,      // O-shaped tetromino
    T,      // T-shaped tetromino
    S,      // S-shaped tetromino
    Z       // Z-shaped tetromino
};

// Enumeration for the indices of sound effects (SFX)
enum SFXIndex
{
    BURN,            // Line clearing sound effect
    TETRIS,          // Tetris (four-line clear) sound effect
    MOVE_SIDEWAYS,   // Sideways movement sound effect
    ROTATE,          // Rotation sound effect
    FIX,             // Piece fixed in place sound effect
    GAME_OVER,       // Game over sound effect
    VICTORY          // Victory sound effect
};

// Enumeration for the different views or states of the game's menu
enum menuViews
{
    TITLE = 0,         // Title screen of the game
    INSTRUCTION_1,     // First instructions screen
    INSTRUCTION_2,     // Second instructions screen
    PLAY,              // Play option in the menu
    EXIT,              // Exit option in the menu
};

// Structure for a tetromino block and its properties
typedef struct
{
    int x;                                  // Current x-coordinate of the tetromino
    int y;                                  // Current y-coordinate of the tetromino
    int rotation;                           // Current rotation state of the tetromino
    int shape[TETROMINO_H][TETROMINO_W];    // Shape matrix representing the tetromino
    int shapeIndex;                         // Index representing the shape of the tetromino
    int move_down;                          // Movement flag for downward motion
    int move_left;                          // Movement flag for leftward motion
    int move_right;                         // Movement flag for rightward motion
    int rotate_;                            // Rotation flag
} Tetromino;

// Structure for player data
typedef struct
{
    char name[4];              // Player's name (3 characters + null terminator)
    int score;                 // Player's score
} player_t;

// Structure for the game's state and properties
typedef struct
{
    int grid[GRID_HEIGHT][GRID_WIDTH];            // Game grid representing the playfield
    int tetrominoGrid[GRID_HEIGHT][GRID_WIDTH];   // Grid representing tetromino positions
    Tetromino activeTetromino;                    // The currently active tetromino
    Tetromino nextTetromino;                      // The next tetromino to spawn
    long score;                                   // Current game score
    int highScoreIndex;                           // Index of the current player's high score
    player_t leaderboard[11];                     // Array of top 10 players and current player data
    int level;                                    // Current game level
    bool hasLevelChanged;                         // Flag indicating if the level has increased
    bool gameOver;                                // Flag indicating if the game is over
    int lines;                                    // Number of lines cleared
    int levelCheckpoint;                          // Threshold for reaching the next level
    int fixDelay;                                 // Buffer for delaying the bottom row movement
    bool quit;                                    // Flag to indicate if the game should quit
    bool pause;                                   // Flag to indicate if the game is paused
    bool redraw;                                  // Flag to indicate if the screen needs redrawing
    bool waitingForExit;                          // Flag indicating if the game is waiting for exit
    int menu;                                     // Current menu state
    int statistics[NUM_SHAPES];                   // Count of appearances for each tetromino shape
    bool restart;                                 // Flag to restart the game
} Game;

/* ----------------- GLOBAL VARIABLES (RASPBERRY) ----------------- */

// The following variables are only used for the Raspberry Pi version of the game
#ifndef PC

extern int digitMatrices[10][8][6];
extern int menuViews[NUMBER_OF_SLIDES][16][16];

#endif // PC

#endif // UTILITIES_h
