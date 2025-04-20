#include "Game.h"



//**************************************************************************
// Prints the current game board
//**************************************************************************
void Game::printGame(){
	board.printOriginalBoard();
	board.printLegend(mario.getLives(), score, mario.getHasHammer());		// Printing lives for user
}


//**************************************************************************
// Showing ESC screen - waiting for user input to resume the game
//**************************************************************************
void Game::showESCScreen() const {
	printScreen(PAUSE_SCREEN);

	while (true) {
		if (_kbhit()) {
			if (_getch() == gameConfig::ESC) {
				break;
			}
		}
	}
}


//**************************************************************************
// Reset a game stage
//**************************************************************************
void Game::resetGameStage(){
	barrels.resetBarrels();
	mario.resetMario();
	ghosts.resetGhosts();
	climbingGhosts.resetGhosts();
	board.resetStage();
	printGame();
}


//**************************************************************************
// Prints game after victory or lose
//**************************************************************************
void Game::printEndGame(bool win) const{
	if (win) {
		printScreen(WIN_SCREEN);
	}
	else {
		printScreen(GAME_OVER_SCREEN);
	}
	printScoreAfterGame();
	while (true) {
		if (_kbhit()) {
			char key = _getch();	// Cleaning buffer - key will be overwritten
			break;
		}
	}

}


//**************************************************************************
// Handle hammer presses
//**************************************************************************
void Game::hammerPressed(){
	if (mario.getHasHammer()) {
		Point newXY = mario.getHammerPoint();
		for (int i = 0; i < gameConfig::HAMMER_KILL_LENGTH; i++) {
			hammerHit(newXY);
			newXY.setOffset(mario.getHammerDirX(), 0);
		}
	}
}


//**************************************************************************
// Calculates score
//**************************************************************************
void Game::calculateScore(){
	gameTimer++;

	if(mario.winState()) {
		int distance = static_cast<int>(board.getStartingMarioPoint().distance(board.getStartingPrincessPoint()));
		score += static_cast<int>(pow(distance, gameConfig::SCORE_DIS_POW) * gameConfig::SCORE_TIME_CONST / (gameTimer + gameConfig::SCORE_TIME_MIN));
		gameTimer = 0;
	}

	score += barrelHit * gameConfig::SCORE_BARREL_MUL;
	barrelHit = 0;

	score += ghostHit * gameConfig::SCORE_GHOST_MUL;
	ghostHit = 0;
}



//**************************************************************************
// Hits a hammer in point
//**************************************************************************
void Game::hammerHit(const Point& position) {
	if (board.isOnBoard(position)) {
		if (board.getCharFromCurr(position) == gameConfig::BARREL_CH || board.getCharFromCurr(position) == gameConfig::GHOST_CH || board.getCharFromCurr(position) == gameConfig::GHOST_CLIMB_LADDER_CH) {
			if (ghosts.findAndKillGhostInPoint(position)) {
				ghostHit++;
				board.renderHammerHit(position);
			}
			if (barrels.findAndKillBarrelInPoint(position)) {
				barrelHit++;
				board.renderHammerHit(position);
			}
			if (climbingGhosts.findAndKillGhostInPoint(position)) {
				ghostHit++;
				board.renderHammerHit(position);
			}
		}
	}
}


//**************************************************************************
// Loads a valid board
//**************************************************************************
bool Game::loadValidBoard(){

	while (currentBoardIndex < filenames.size()) {
		updateSteps();
		updateResults();
		lastScreenScore = score;
		if (board.load(filenames[currentBoardIndex])) {
			resetGameStage();
			return true;
		}
		else {
			printErrorWithBoard();
			currentBoardIndex++;
		}
	}
	return false;
}


void Game::drawChangesOnBoard(){
	ghosts.drawGhosts();
	barrels.drawBarrels();
	mario.draw();
	board.printLegend(mario.getLives(), score, mario.getHasHammer());

}


bool Game::cmpDeathToResult(){
	if (!results.isFinishedBy(gameIterCounter) || !results.cmp(gameIterCounter, Results::died)) {
		return false;
	}
	return true;
}


bool Game::cmpWinToResult(){
	if (!results.isFinishedBy(gameIterCounter) || !results.cmp(gameIterCounter, Results::finished)) {
		return false;
	}
	return true;
}


bool Game::cmpScoreToResult(){
	if (!results.isFinishedBy(gameIterCounter) || !results.cmp(score - lastScreenScore, Results::score)) {
		return false;
	}
	return true;
}


//**************************************************************************
// Prints Error with board
//**************************************************************************
void Game::printErrorWithBoard(){
	if (!board.getPrintMode()) { return; }
	printScreen(ERROR_SCREEN);
	Point errorPoint(gameConfig::ERROR_PRINT_X, gameConfig::ERROR_PRINT_Y);
	gotoxy(errorPoint);
	if (board.getInvalidChars()) {
		errorPoint.goDown();
		gotoxy(errorPoint);
		std::cout << "- Invalid characters on the board!";
	}
	else if (board.getWidthTooShort()) {
		errorPoint.goDown();
		gotoxy(errorPoint);
		std::cout << "- Board width is too short!";
	}
	else if (board.getHeightTooShort()) {
		errorPoint.goDown();
		gotoxy(errorPoint);
		std::cout << "- Board height is too short!";
	}
	else if (board.getStartingDonkeyPoint() == Point::NOT_FOUND) {
		errorPoint.goDown();
		gotoxy(errorPoint);
		std::cout << "- Donkey is missing from the board!";
	}
	else if (board.getStartingMarioPoint() == Point::NOT_FOUND) {
		errorPoint.goDown();
		gotoxy(errorPoint);
		std::cout << "- Mario is missing from the board!";
	}
	else if(board.getStartingPrincessPoint() == Point::NOT_FOUND){
		errorPoint.goDown();
		gotoxy(errorPoint);
		std::cout << "- Princess is missing from the board!";
	}

	Sleep(gameConfig::ERROR_SCREEN_SLEEP);
}


void Game::printResults(bool deaths, bool win, bool score){
	printScreen(RESULTS_SCREEN);
	Point printPoint(gameConfig::RESULTS_PRINT_X, gameConfig::RESULTS_PRINT_Y);
	gotoxy(printPoint);
	if (!deaths) {
		std::cout << "Results failed - death not match";
	}
	else if (!win) {
		std::cout << "Results failed - win not match";
	}
	else if (!score) {
		std::cout << "Results failed - score not match";
	}
	else {
		std::cout << "Results passed";
	}
	gotoxy(printPoint.below());
	std::cout << "Screen: " << filenames[currentBoardIndex] << std::endl;	// Assumes name not to big- not crashing
	Sleep(gameConfig::RESULTS_SCREEN_TIME);
}


//**************************************************************************
// Main game loop - while Mario is alive, running the game
// Returning bool if the user won or lost the game
//**************************************************************************
void Game::run() {

	if (!loadValidBoard()) {
		printEndGame(false);
		return;
	}

	while (mario.getLives() > 0 && gameRunning) {		// While alive
		gameIterCounter++;

		ghosts.updateGhosts();		// Ghosts logic
		climbingGhosts.updateGhosts();		// Ghosts logic
		barrels.updateBarrels();	// Barrels logic

		Sleep(gameSpeed);

		getInput();		// Getting input
		mario.updateMario();		// Mario logic

		calculateScore();
		board.printLegend(mario.getLives(), score, mario.getHasHammer());		// Printing lives for user
		
		if(!mario.isAlive() && mario.getLives() > 0) {		// If Mario dies - resetting the game
			marioDied();
		}
		else if (mario.winState()) {	// If won
			finishedScreen(true);
			currentBoardIndex++;
			if (!loadValidBoard()) {
				printEndGame(true);
				return;
			}
			gameIterCounter = 0;
		}
		else if (mario.getLives() == 0 || !gameRunning) {	// lost
			finishedScreen(false);
			currentBoardIndex++;
			updateSteps();	// FIX - updating steps after game ends
			updateResults();
			printEndGame(false);
			return;	// Lives <= 0
		}
		if(continueToNextScreen) {
			continueToNextScreen = false;
			currentBoardIndex++;
			if (!loadValidBoard()) {
				printEndGame(true);
				return;
			}
			gameIterCounter = 0;
		}
	}
}


bool Game::processInput(char firstKey, char secondKey){
	bool validKey = false;

	if (firstKey == gameConfig::ESC || secondKey == gameConfig::ESC) {
		showESCScreen();
		getBoard().printCurrentBoard();
	}
	else if (std::tolower(firstKey) == 'p') {
		validKey = true;
		hammerPressed();
		if (secondKey != gameConfig::CHAR_NOT_FOUND) {
			getMario().keyPressed(secondKey);
		}
	}
	else {
		validKey = getMario().keyPressed(firstKey);	// Sending key to mario to be evaluated
		if (secondKey != gameConfig::CHAR_NOT_FOUND) {
			if (std::tolower(secondKey) == 'p') {
				validKey = true;
				hammerPressed();
			}
		}
	}
	return validKey;
}


//**************************************************************************
// Prints the score at the end of the game
//**************************************************************************
void Game::printScoreAfterGame() const{

	int x = gameConfig::SCORE_PRINT_AFTER_GAME_X;
	int y = gameConfig::SCORE_PRINT_AFTER_GAME_Y;
	gotoxy(Point(x, y));
	std::cout << "SCORE:" << score << std::endl;

}