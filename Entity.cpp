#include "Entity.h"


//**************************************************************************
// Moves an entity
//**************************************************************************
bool Entity::move(bool throughFloor){
	Point next = getNextPos();
	if (pBoard->isOnBoard(next)) {
		if (throughFloor) {
			xy = next;
		}
		else {	// not through walls
			if (pBoard->isFloor(next)) {
				dir = gameConfig::STAY;
			}
			else {
				xy = next;
			}
		}
		return true;
	}
	return false;
}


//**************************************************************************
// Moves an entity
//**************************************************************************
bool Entity::move(int xOffset, int yOffset, bool throughFloor){
	bool res;
	gameConfig::Direction tempDir(dir);
	dir.x = xOffset;
	dir.y = yOffset;
	res = move(throughFloor);
	dir = tempDir;
	return res;
}


//**************************************************************************
// Checks if on ladder
//**************************************************************************
bool Entity::isOnLadder() const{

	if (pBoard->isLadder(xy)) {		// current position is a ladder
		return true;
	}
	else if (xy.below().getY() > gameConfig::GAME_HEIGHT - 1) {	// If can read button char
		return false;
	}
	else if (pBoard->isLadder(xy.below())) {	// button position is a ladder
		return true;
	}
	else {	// not on a ladder
		return false;
	}
}


//**************************************************************************
// checks if possible to go down a ladder
//**************************************************************************
bool Entity::isOnLadderDown() const{
	// Check if can read 2 button char
	if (xy.copyWithOffset(0, 2).getY() > gameConfig::GAME_HEIGHT - 1) {
		return false;
	}
	// Checks if the button char is a floor and the 2 down are a ladder
	else if (pBoard->isLadder(xy.copyWithOffset(0, 2)) && pBoard->isFloor(xy.below())) {
		return true;
	}
	// Not on ladder going down
	else {
		return false;
	}
}
