#include "Ghosts.h"


//**************************************************************************
// Randomize the direction of a specific ghost based on probability
//**************************************************************************
void Ghosts::randomizeDirection(int index){
	int change = (rand() % 100 < gameConfig::GHOST_CHANGE_PROB) ? 1 : -1;
	gameConfig::Direction currDir = getEntityDirection(index);
	currDir.x *= change;
	setEntityDirection(index, currDir);
}



//**************************************************************************
// updates all ghosts
//**************************************************************************
void Ghosts::updateGhosts(){
	int size = getEntitiesSize();

	for (int i = 0; i < size; i++) {
		eraseGhost(i);
		//updateDirection(i);
		moveGhost(i);
		drawGhost(i);
	}
}


//**************************************************************************
// Finds ghosts on the map and add to the vector
//**************************************************************************
void Ghosts::activateGhosts(){
	int num = 0;
	Point ghostPoint = pBoard->findCharacter(getChar(), num + 1);	// FIX TO ENEMY CHARACTER
	gameConfig::Direction dir;

	while(ghostPoint != Point::NOT_FOUND){
		dir = (rand() & 1) ? gameConfig::RIGHT : gameConfig::LEFT;
		addEntity(ghostPoint, dir);
		
		num++;
		ghostPoint = pBoard->findCharacter(getChar(), num + 1);
	}
}


//**************************************************************************
// deletes all current ghosts. searching for new ones
//**************************************************************************
void Ghosts::resetGhosts(){
	deleteAllGhosts();
	activateGhosts();
}


//**************************************************************************
// Erases current ghosts
//**************************************************************************
void Ghosts::eraseGhosts(){
	int size = getEntitiesSize();
	for (int i = 0; i < size; i++){
		eraseGhost(i);
	}
}



//**************************************************************************
// Decides a random dir right or left 50 50
//**************************************************************************
void Ghosts::setRandomDir(int index){
	setEntityDirection(index, (rand() & 1) ? gameConfig::RIGHT : gameConfig::LEFT);
}



//**************************************************************************
// Check if current dir is valid, changes other ghost's dir if collision
//**************************************************************************
bool Ghosts::checkDirValid(int index) {
	gameConfig::Direction dir = getEntityDirection(index);
	Point currentPoint = getEntityPoint(index);
	
	if (pBoard->isFloor(currentPoint.copyWithOffset(dir.x, 1))) {	// continuing on floor
		if (pBoard->isEnemyInPoint(currentPoint.copyWithOffset(dir.x, dir.y))) {	// if Ghost/Barrel there
			reverseEntityDir(findGhostInPoint(currentPoint.copyWithOffset(dir.x, dir.y)));
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}


//**************************************************************************
// Updates the direction of a specific ghost
//**************************************************************************
void Ghosts::updateDirection(int index) {
	if (getEntityDirection(index).x == 0) {	// if ghost was in stay
		setRandomDir(index);
	}

	randomizeDirection(index);

	if (!checkDirValid(index)) {
		reverseEntityDir(index);
		if (!checkDirValid(index)) {
			setEntityDirection(index, gameConfig::STAY);
		}
	}
}


//**************************************************************************
// Finds the index in the vector of a ghosts in a specific point. returns not found if not found
//**************************************************************************
int Ghosts::findGhostInPoint(const Point position) const{

	int size = getEntitiesSize();
	for (int i = 0; i < size; i++) {
		if (getEntityPoint(i) == position) {
			return i;
		}
	}
	return gameConfig::NOT_FOUND;
}


//**************************************************************************
// Finds a ghost in a point and deletes it
//**************************************************************************
bool Ghosts::findAndKillGhostInPoint(const Point position){
	int index = findGhostInPoint(position);
	if (index != gameConfig::NOT_FOUND) {
		deleteGhost(index);
		return true;
	}
	return false;
}


//**************************************************************************
// Draw all ghosts
//**************************************************************************
void Ghosts::drawGhosts(){
	drawEntities();
}


//**************************************************************************
// Draw a specific ghost
//**************************************************************************
void Ghosts::drawGhost(int index){
	drawEntity(index);
}


//**************************************************************************
// Move a specific ghost
//**************************************************************************
void Ghosts::moveGhost(int index){
	updateDirection(index);
	moveEntity(index);
}
