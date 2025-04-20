#include "ClimbingGhosts.h"




void ClimbingGhosts::moveGhost(int index){
	bool ghostOnLadder = isOnLadder(index);
	bool ghostOnLadderDown = isOnLadderDown(index);
	bool ghostOnFloor = isOnFloor(index);
	Point marioPos = pBoard->getMarioPoint();

	// X bias is not used because we still want ghots to wander on the platform
	//int xBias = marioPos.getX() - getEntityPoint(index).getX();		// If positive, mario is to the right
	int yBias = marioPos.getY() - getEntityPoint(index).getY();		// If positive, mario is below


	if (ghostOnLadder && ghostOnFloor) {	// Going up
		if (yBias < 0) {
			climbLadderUpEntity(index);
			return;
		}
	}
	else if (ghostOnLadderDown && ghostOnFloor) {	// Going down
		if (yBias > 0) {
			climbLadderDownEntity(index);
			return;
		}
	}
	else if (ghostOnLadder) {		// Middle of ladder
		if (yBias > 0) {
			climbLadderDownEntity(index);
		}
		else{
			climbLadderUpEntity(index);
		}
		return;
	}
	else {
		randomizeDirection(index);
	}


	if (getEntityDirection(index).x == 0) {	// if ghost was in stay
		setRandomDir(index);
	}

	if (!checkDirValid(index)) {
		reverseEntityDir(index);
		if (!checkDirValid(index)) {
			setEntityDirection(index, gameConfig::STAY);
		}
	}

	moveEntity(index);
}
