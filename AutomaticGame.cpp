#include "AutomaticGame.h"


void AutomaticGame::getInput(){
	if (isNextStepSaved()) {
		char firstKey = getStep();
		if (isNextStepSaved()) {
			char secondKey = getStep();
			processInput(firstKey, secondKey);
		}
		else {
			processInput(firstKey);
		}
	}
}
