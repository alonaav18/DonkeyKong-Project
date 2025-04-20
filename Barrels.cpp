#include "Barrels.h"


//**************************************************************************
// Resetting barrel and activating barrel 
//**************************************************************************
void Barrels::createNewBarrel(){
	gameConfig::Direction dir = (rand() & 1) ? gameConfig::RIGHT: gameConfig::LEFT;	// Random direction - bitwise faster than % 2
	addEntity(spawnLocation, dir);
	explodeTimer.push_back(0);
}



//**************************************************************************
// Resetting and clearing barrels
//**************************************************************************
void Barrels::resetBarrels(){

	spawnLocation = pBoard->getStartingDonkeyPoint();
	deleteAllBarrels();
	newBarrelTimer = gameConfig::NEW_BARREL_TIMER;
}


//**************************************************************************
// Check if barrel needs to explode
//**************************************************************************
bool Barrels::checkExplosion(int index){
	if (isOnFloor(index)) {
		if (explodeTimer[index] >= gameConfig::BARREL_EXPLODING_TIMER) {
			barrelExplode(index);
			return true;
		}
		else {
			explodeTimer[index] = 0;
			return false;
		}
	}
	else {
		return false;
	}
}


//**************************************************************************
// Setting a barrel's direction based on the floor sign
//**************************************************************************
void Barrels::updateDirection(int index){
	Point barrelPoint = getEntityPoint(index);
	if (pBoard->isOnBoard(barrelPoint.below())) {
		char signFloor = pBoard->getCharFromOrig(barrelPoint.below());

		if (signFloor == gameConfig::FLOOR_LEFT_CH) {
			setEntityDirection(index, gameConfig::LEFT);
		}
		else if (signFloor == gameConfig::FLOOR_RIGHT_CH) {
			setEntityDirection(index, gameConfig::RIGHT);
		}
	}
}


//**************************************************************************
// Main barrels function for updating the barrel - clearing moving - drawing
//**************************************************************************
void Barrels::updateBarrels(){

	releaseBarrel();

	for (int i = 0; i < getEntitiesSize(); i++) {
		if (!checkExplosion(i)) {
			eraseBarrel(i);
			moveBarrel(i);
		}
		else {
			i--;
		}
	}
	drawBarrels();
}



//**************************************************************************
// Make a Barrel fall
//**************************************************************************
void Barrels::fall(int index){
	moveEntityDown(index);
	explodeTimer[index]++;
}


//**************************************************************************
// Checking if a barrel should fall
//**************************************************************************
bool Barrels::isFalling(int index) const {
	return (!isOnFloor(index) && pBoard->isOnBoard(getEntityPoint(index).below()));	// Not on floor and not overflowing board
}



//**************************************************************************
// Drawing the active barrels
//**************************************************************************
void Barrels::drawBarrels(){
	drawEntities();
}


//**************************************************************************
// Make a barrel explode - checking if Mario needs to be killed
//**************************************************************************
void Barrels::barrelExplode(int index){
	Point barrelPoint = getEntityPoint(index);
	deleteBarrel(index);
	Point marioPoint = pMario->getXY();
	int distanceX = abs(marioPoint.getX() - barrelPoint.getX());
	int distanceY = abs(marioPoint.getY() - barrelPoint.getY());
	if (distanceX <= gameConfig::BARREL_EXPLOAD_DISTANCE && distanceY <= gameConfig::BARREL_EXPLOAD_DISTANCE) {	// Distance from Mario
		pBoard->renderExplosion(barrelPoint);	// BONUS point - checking inside for special mode
		pMario->killMario();
	}
}


//**************************************************************************
// Finds a barrel in point
//**************************************************************************
int Barrels::findBarrelInPoint(const Point position) const{
	int size = getEntitiesSize();

	for (int i = 0; i < size; i++) {
		if (getEntityPoint(i) == position) {
			return i;
		}
	}
	return gameConfig::NOT_FOUND;
}


//**************************************************************************
// Finds and kill a barrel
//**************************************************************************
bool Barrels::findAndKillBarrelInPoint(const Point& position){
	int index = findBarrelInPoint(position);
	if (index != gameConfig::NOT_FOUND) {
		deleteBarrel(index);
		return true;
	}
	return false;
}


//**************************************************************************
// Deletes all barrels
//**************************************************************************
void Barrels::deleteAllBarrels(){
	removeAllEntities();
	explodeTimer.clear();
	explodeTimer.shrink_to_fit();
}


//**************************************************************************
// Checking if a new barrel should be released based on timer and max barrels
//**************************************************************************
void Barrels::releaseBarrel(){
	if (newBarrelTimer <= 0) {
		createNewBarrel();
		newBarrelTimer = gameConfig::NEW_BARREL_TIMER;
	}
	else {
		newBarrelTimer--;
	}
}


//**************************************************************************
// Clears a single barrel
//**************************************************************************
void Barrels::eraseBarrel(int index){
	eraseEntity(index);
}


//**************************************************************************
// Clears all active barrels
//**************************************************************************
void Barrels::eraseAllBarrels(){
	int size = getEntitiesSize();

	for (int i = 0; i < size; i++) {
		eraseBarrel(i);
	}
}


//**************************************************************************
// Moving a single barrel
//**************************************************************************
void Barrels::moveBarrel(int index){

	if (isFalling(index)){
		fall(index);
	}
	else {
		updateDirection(index);
		if (!moveEntity(index)) {	// Managed to move (stayed on board)
			deleteEntity(index);
		}
	}
}