#include "SilentGame.h"

void SilentGame::marioDied() {
	updateDeathResult();
	if(!continueToNextScreen){
		resetGameStage();
	}
}


void SilentGame::finishedScreen(bool screenWon){
	bool printed = false;
	if (screenWon) {
		if (!cmpWinToResult()) {
			getBoard().setPrintOn();
			printResults(true, false, true);
			getBoard().setPrintOff();
			printed = true;
		}
	}
	else {
		if (!cmpDeathToResult()) {
			getBoard().setPrintOn();
			printResults(false, true, true);
			getBoard().setPrintOff();
			printed = true;
		}
	}
	if (!printed && !cmpScoreToResult()) {
		getBoard().setPrintOn();
		printResults(true, true, false);
		getBoard().setPrintOff();
	}
	else if (!printed){
		getBoard().setPrintOn();
		printResults(true, true, true);
		getBoard().setPrintOff();
	}
}


void SilentGame::updateDeathResult(){
	if (!cmpDeathToResult()) {
		getBoard().setPrintOn();
		printResults(false, true, true);
		getBoard().setPrintOff();
		continueToNextScreenTrue();
	}
}
