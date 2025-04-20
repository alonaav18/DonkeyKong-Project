#pragma once
#include "Point.h"

class gameConfig {
public:

	static constexpr int NOT_FOUND = -1;
	static constexpr char CHAR_NOT_FOUND = -1;


	// SIZES
	static constexpr int GAME_WIDTH = 80;
	static constexpr int GAME_HEIGHT = 25;


	// TIMERS
	static constexpr int GAME_SPEED = 150;
	static constexpr int GAME_SPEED_LOAD = 20;
	static constexpr int GAME_SPEED_SILENT = 0;
	static constexpr int PREMENU_TIME = 1500; 


	// KEYS
	static constexpr int ESC = 27;
	static constexpr int MENU_START_GAME = '1';
	static constexpr int MENU_SPECIAL_MODE = '2';
	static constexpr int MENU_START_FROM_FILE = '3';
	static constexpr int MENU_SHOW_INSTRUCTIONS = '8';
	static constexpr int MENU_EXIT_GAME = '9';
	static constexpr int MENU_NEXT_SCREEN = 'd';
	static constexpr int MENU_BACK_SCREEN = 'a';
	static constexpr int MENU_BACK_FROM_INSTRUCTIONS = ESC; 
	enum {UP_KEY = 'w' , LEFT_KEY = 'a', DOWN_KEY = 'x', RIGHT_KEY = 'd', STAY_KEY = 's' };



	// MAP CHARS	// FIX INT
	static constexpr int MARIO_CH = '@';
	static constexpr int LADDER_CH = 'H';
	static constexpr int GHOST_CH = 'x';
	static constexpr int GHOST_CLIMB_LADDER_CH = 'X';
	static constexpr int LEGEND_CH = 'L';
	static constexpr int HAMMER_CH = 'p';
	static constexpr int DONKEY_CH = '&';
	static constexpr int PRINCESS_CH = '$';
	static constexpr int BARREL_CH = 'O';
	static constexpr int FLOOR_RIGHT_CH = '>';
	static constexpr int FLOOR_STRAIGHT_CH = '=';
	static constexpr int FLOOR_LEFT_CH = '<';
	static constexpr int WALL_CH = 'Q';



	// COLORS
	static constexpr int DEFAULT_COLOR = 7;
	static constexpr int HAMMER_COLOR = 7;
	static constexpr int STRAIGHT_FLOOR_COLOR = 4;
	static constexpr int DONKEY_COLOR = 6;
	static constexpr int LADDER_COLOR = 11;
	static constexpr int PRINCESS_COLOR = 10;
	static constexpr int EXPLOSION_COLOR = 6;
	static constexpr int BARRELS_COLOR = 6;
	static constexpr int MARIO_COLOR = 15;

	static constexpr int LEGEND_HAMMER_COLOR = 1;
	static constexpr int LEGEND_LIVES_COLOR = 4;
	static constexpr int LEGEND_SCORE_COLOR = 13;


	// MARIO
	static constexpr int MARIO_STARTING_LIVES = 3;
	static constexpr int MARIO_MAX_FALL = 5; 
	static constexpr int MARIO_JUMP_HEIGHT= 2;
	static constexpr int HAMMER_KILL_LENGTH = 2;

	

	// MENU
	static constexpr bool DEFAULT_SPECIAL_MODE = true;
	static constexpr int MAX_FILES_IN_SCREEN = 10; 
	static constexpr int START_SCREEN = 0;

	static constexpr int CHOOSE_FILE_LOC_X = 12;	// File location starting print point in menu
	static constexpr int CHOOSE_FILE_LOC_Y = 4; 
	static constexpr int SPECIAL_MODE_Y = 16;	// True/False print on menu
	static constexpr int SPECIAL_MODE_X = 27;



	// SCORE
	static constexpr int SCORE_TIME_CONST = 20; 
	static constexpr double SCORE_DIS_POW = 2;
	static constexpr int SCORE_TIME_MIN = 200;
	static constexpr int SCORE_BARREL_MUL = 50; 
	static constexpr int SCORE_GHOST_MUL = 50; 
	
	static constexpr int SCORE_PRINT_AFTER_GAME_X = 35;		// End game screen score location
	static constexpr int SCORE_PRINT_AFTER_GAME_Y = 19;


	// Game
	static constexpr int ERROR_PRINT_Y = 6;	// Error with board print location
	static constexpr int ERROR_PRINT_X = 26;
	static constexpr int ERROR_SCREEN_SLEEP = 2500;

	static constexpr int RESULTS_SCREEN_TIME = 1500;
	static constexpr int RESULTS_PRINT_X = 28;
	static constexpr int RESULTS_PRINT_Y = 10;


	// BARRELS
	static constexpr int EXPLOSION_ANIMATION_DELAY = 175;
	static constexpr int BARREL_EXPLOAD_DISTANCE = 2;
	static constexpr int NEW_BARREL_TIMER = 10;
	static constexpr int BARREL_EXPLODING_TIMER = 8;

	// GHOST
	
	static constexpr int GHOST_CHANGE_PROB = 95;  // Out of 100

	//DIRECTIONS
	struct Direction { int x, y; }; // inner private struct
	static constexpr Direction LEFT = { -1,0 };
	static constexpr Direction RIGHT = { 1,0 };
	static constexpr Direction STAY = { 0,0 };
	static constexpr Direction DOWN = { 0,1 };
	static constexpr Direction UP = { 0,-1 };



	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr char keys[] = { UP_KEY, LEFT_KEY, DOWN_KEY, RIGHT_KEY, STAY_KEY};
	static constexpr Direction directions[] = {STAY, LEFT, STAY, RIGHT, STAY};
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
};