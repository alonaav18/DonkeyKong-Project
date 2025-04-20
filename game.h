#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

#include "gameConfig.h"
#include "utils.h"
#include "Board.h"
#include "Mario.h"
#include "Barrels.h"
#include "Ghosts.h"
#include "ClimbingGhosts.h"
#include "Steps.h"
#include "Results.h"


class Game{
	bool specialMode = false;	// Special mode for bonus points	// Keep order before board - as it's being sent in the constructor
	bool gameRunning = true;

	long seed = 0;
	Board board;
	Results results;
	Steps steps;
	Mario mario;
	Barrels barrels;
	Ghosts ghosts;
	ClimbingGhosts climbingGhosts;
	std::vector<std::string> filenames = {};
	int currentBoardIndex = 0;
	size_t gameIterCounter = 0;
	int gameSpeed = gameConfig::GAME_SPEED;


	int score = 0;
	int lastScreenScore = 0;

	int gameTimer = 0;	// for specific board // FIX
	int barrelHit = 0;
	int ghostHit = 0;

	const char* PAUSE_SCREEN[gameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************",// 0
		  "*                                                                              *",// 1
		  "*                                                                              *",// 2
		  "*             .______      ___      __    __       _______. _______            *", // 3
		  "*             |   _  \\    /   \\    |  |  |  |     /       ||   ____|           *", // 4
		  "*             |  |_)  |  /  ^  \\   |  |  |  |    |   (----`|  |__              *", // 5
		  "*             |   ___/  /  /_\\  \\  |  |  |  |     \\   \\    |   __|             *", // 6
		  "*             |  |     /  _____  \\ |  `--'  | .----)   |   |  |____            *", // 7
		  "*             | _|    /__/     \\__\\ \\______/  |_______/    |_______|           *", // 8
		  "*                                                                              *",// 9
		  "*                                                                              *",// 10
		  "*  ==========================================================================  *",// 11
		  "*                                                                              *",// 12
		  "*                                                                              *",// 13
		  "*                              THE GAME IS PAUSED                              *",// 14
		  "*                                                                              *",// 15
		  "*                       Press ESC to continue the game.                        *",// 16
		  "*                                                                              *",// 17
		  "*                                                                              *",// 18
		  "*                                                                              *",// 19
		  "*  ==========================================================================  *",// 20
		  "*                                                                              *",// 21
		  "*                                                                              *",// 22
		  "*                                                                              *",// 23
		  "********************************************************************************" // 24
	};

	const char* RESULTS_SCREEN[gameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************",// 0
		  "*                                                                              *",// 1
		  "*                                                                              *",// 2
		  "*                                                                              *",// 3
		  "*                                                                              *",// 4
		  "*                                                                              *",// 5
		  "*                                                                              *",// 6
		  "*                                                                              *",// 7
		  "*                                                                              *",// 8
		  "*                                                                              *",// 9
		  "*                                                                              *",// 10
		  "*                                                                              *",// 11
		  "*                                                                              *",// 12
		  "*                                                                              *",// 13
		  "*                                                                              *",// 14
		  "*                                                                              *",// 15
		  "*                                                                              *",// 16
		  "*                                                                              *",// 17
		  "*                                                                              *",// 21
		  "*                                                                              *",// 22
		  "*                                                                              *",// 18
		  "*                                                                              *",// 19
		  "*                                                                              *",// 20
		  "*                                                                              *",// 23
		  "********************************************************************************" // 24
	};

	const char* ERROR_SCREEN[gameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************",// 0
		  "*                                                                              *",// 1
		  "*                                                                              *",// 2
		  "*                                                                              *",// 3
		  "*                                                                              *",// 4
		  "*                       Loading the screen failed due to:                      *",// 5
		  "*                                                                              *",// 6
		  "*                                                                              *",// 7
		  "*                                                                              *",// 8
		  "*                                                                              *",// 9
		  "*                                                                              *",// 10
		  "*                                                                              *",// 11
		  "*                                                                              *",// 12
		  "*                                                                              *",// 13
		  "*                                                                              *",// 14
		  "*                                                                              *",// 15
		  "*                                                                              *",// 16
		  "*                                                                              *",// 17
		  "*                                                                              *",// 21
		  "*                                                                              *",// 22
		  "*                                                                              *",// 18
		  "*                                                                              *",// 19
		  "*                                                                              *",// 20
		  "*                                                                              *",// 23
		  "********************************************************************************" // 24
	};


	const char* WIN_SCREEN[gameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************",// 0
		  "*                                                                              *",// 1
		  "*                                                                              *",// 2
		  "*                                                                              *",// 3
		  "*  ____    ____  ______    __    __     ____    __    ____  ______   .__   __. *",// 4
		  "*  \\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / /  __  \\  |  \\ |  | *",// 5
		  "*   \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   / |  |  |  | |   \\|  | *",// 6
		  "*    \\_    _/  |  |  |  | |  |  |  |      \\            /  |  |  |  | |  . `  | *",// 7
		  "*      |  |    |  `--'  | |  `--'  |       \\    /\\    /   |  `--'  | |  |\\   | *",// 8
		  "*      |__|     \\______/   \\______/         \\__/  \\__/     \\______/  |__| \\__| *",// 9
		  "*                                                                              *",// 10
		  "*                                                                              *",// 11
		  "*                                                                              *",// 12
		  "*                                                                              *",// 13
		  "*                                                                              *",// 14
		  "*                                                                              *",// 15
		  "*                                                                              *",// 16
		  "*                                                                              *",// 17
		  "*                                                                              *",// 21
		  "*                                                                              *",// 22
		  "*  ==========================================================================  *",// 18
		  "*                          PRESS ANY KEY TO CONTINUE                           *",// 19
		  "*  ==========================================================================  *",// 20
		  "*                                                                              *",// 23
		  "********************************************************************************" // 24
	};


	const char* GAME_OVER_SCREEN[gameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "********************************************************************************",// 0
		  "*                                                                              *",// 1
		  "*                                                                              *",// 2
		  "*                    _______      ___      .___  ___.   _______                *",// 3
		  "*                   /  _____|    /   \\     |   \\/   |  |   ____|               *",// 4 
		  "*                  |  |  __     /  ^  \\    |  \\  /  |  |  |__                  *",// 5 
		  "*                  |  | |_ |   /  /_\\  \\   |  |\\/|  |  |   __|                 *",// 6
		  "*                  |  |__| |  /  _____  \\  |  |  |  |  |  |____                *",// 7
		  "*                   \\______| /__/     \\__\\ |__|  |__|  |_______|               *",// 8
		  "*                                                                              *",// 9
		  "*                    ______   ____    ____  _______   .______                  *",// 10
		  "*                   /  __  \\  \\   \\  /   / |   ____|  |   _  \\                 *",// 11
		  "*                  |  |  |  |  \\   \\/   /  |  |__     |  |_)  |                *",// 12
		  "*                  |  |  |  |   \\      /   |   __|    |      /                 *",// 13
		  "*                  |  `--'  |    \\    /    |  |____   |  |\\  \\-.               *",// 14
		  "*                   \\______/      \\__/     |_______|  | _| `.__|               *",// 15
		  "*                                                                              *",// 16
		  "*                                                                              *",// 17
		  "*                                                                              *",// 22
		  "*                                                                              *",// 21
		  "*  ==========================================================================  *",// 18
		  "*                           PRESS ANY KEY TO CONTINUE                          *",// 19
		  "*  ==========================================================================  *",// 20
		  "*                                                                              *",// 23
		  "********************************************************************************" // 24
	};


protected:
	Game(bool specialMode_, std::vector<std::string> filenames_, int index) :	// Constructor
			specialMode(specialMode_),	// Keep order
			filenames(filenames_),
			currentBoardIndex(index),
			board(specialMode, filenames_[index]),
			mario(&board),
			barrels(&board, &mario),
			ghosts(&board),
			climbingGhosts(&board)
	{}
	virtual ~Game() {}


	bool continueToNextScreen = false;
	Mario& getMario() { return mario; }
	Board& getBoard() { return board; }
	Barrels& getBarrels() { return barrels; }
	Ghosts& getGhosts() { return ghosts; }



public:
	void printScoreAfterGame() const;	// FIX RESULTS
	virtual void getInput() = 0;
	virtual void updateSteps() = 0;
	void run();
	bool processInput(char firstKey, char secondKey = gameConfig::CHAR_NOT_FOUND);
	virtual void printGame();
	void showESCScreen() const;
	void resetGameStage();
	virtual void printEndGame(bool win) const;
	void calculateScore();
	void hammerPressed();
	void hammerHit(const Point& position);
	bool loadValidBoard();
	virtual void drawChangesOnBoard();
	virtual void updateResults() = 0;
	virtual void updateDeathResult() = 0;

	virtual void marioDied() = 0;
	virtual void finishedScreen(bool screenWon) = 0;

	void loadScreenResults() { results.clrResults(); results = Results::loadResults(filenames[currentBoardIndex]);}
	void saveScreenResults() { if (currentBoardIndex > 0) { results.saveResults(filenames[currentBoardIndex - 1]); results.clrResults(); } }
	void addDeathToResult() { results.addResult(gameIterCounter, Results::died); }
	void addWinToResult() { results.addResult(gameIterCounter, Results::finished); }
	void addScoreToResult() { if (currentBoardIndex > 0) { results.addResult(score-lastScreenScore, Results::score); } }
	bool cmpDeathToResult();
	bool cmpWinToResult();
	bool cmpScoreToResult();


	void loadScreenSteps() { steps.clrSteps(); steps = Steps::loadSteps(filenames[currentBoardIndex]); setRandomSeed(steps.getLoadedSeed()); }
	void saveScreenSteps() { if (currentBoardIndex > 0) { steps.saveSteps(filenames[currentBoardIndex - 1]); steps.clrSteps(); } }

	bool isNextStepSaved() { return steps.isNextStepOnIteration(gameIterCounter); }
	char getStep() { return steps.popStep(); }
	void setRandomSeed(long seed_) { seed = seed_; srand(seed);  steps.setRandomSeed(seed); }
	void addStepToGame(char step) { steps.addStep(gameIterCounter, step); }
	void printErrorWithBoard();
	void setGameSpeed(int speed){ gameSpeed = speed; }
	void printResults(bool deaths, bool win, bool score);
	void continueToNextScreenTrue(){ continueToNextScreen = true; }
};