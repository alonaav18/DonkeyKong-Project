#include "ManualGame.h"




//**************************************************************************
// Getting user's input and updating the game
//**************************************************************************
void ManualGame::getInput(){
	// We want to let Mario get a hammer and move at the same turn.
	// But not allow to move twice, and get hammer twice.
	char firstKey;
	char secondKey;
	bool validKey = false;

	if (_kbhit()) {
		 firstKey = _getch();
		if(_kbhit()){
			secondKey =_getch();	// Cleaning buffer - key will be overwritten
			validKey = processInput(firstKey, secondKey);
			if (saveMode && validKey) { addStepToGame(firstKey); addStepToGame(secondKey); }
		}
		else {
			validKey = processInput(firstKey);
			if (saveMode && validKey) { addStepToGame(firstKey); }
		}
	}
}


