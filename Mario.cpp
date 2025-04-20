#include "Mario.h"


//**************************************************************************
// Prints Mario's character on the board
//**************************************************************************
void Mario::draw(){
	Entity::draw();
	pBoard->setMarioPoint(getXY());
}


//**************************************************************************
// Erases Mario's character from the board unless he is overlapped by a barrel
//**************************************************************************
void Mario::eraseMario(){
	erase();
}


//**************************************************************************
// Resets Mario for a new game
//**************************************************************************
void Mario::resetMario(){
	setXY(pBoard->getStartingMarioPoint());
	setSpawnPoint(getXY());
	eraseMario();
	win = false;
	alive = true;
	updateState();
	setDir(gameConfig::STAY);
	jumpTimer = 0;
	fallCounter = 0;
	hasHammer = false;
	pBoard->setHammerLost();
}


//**************************************************************************
// Handles Mario after user input
//**************************************************************************
bool Mario::keyPressed(char key) {
	updateState();
	
	char lowerKey = std::tolower(key);
	for (size_t i = 0; i < gameConfig::numKeys; i++) {
		if (lowerKey == gameConfig::keys[i]) {
			if (lowerKey == gameConfig::UP_KEY) {	// UP
				handleUpMovement();
			}
			else if (lowerKey == gameConfig::DOWN_KEY) { // Down
				handleDownMovement();
			}
			else{	// Move sideways or stay
				ladderGoingDown = false;
				ladderGoingUp = false;
				setDir(gameConfig::directions[i]);
				if (getDir().x != 0) {
					hammerDirX = getDir().x;
				}
			}
			return true;
		}
	}
	return false;
}


//**************************************************************************
// Handles movement up
//**************************************************************************
void Mario::handleUpMovement(){
	if (!onLadder && !onFloor) {	// falling can only go sideways
		return;
	}
	if (!onLadder && jumpTimer == 0) {	// start to jump - stay on right/left dir
		jumpTimer = gameConfig::MARIO_JUMP_HEIGHT;
		return;
	}
	else {	// Climb ladder
		ladderGoingUp = true;
		ladderGoingDown = false;
		setDir(gameConfig::STAY);
		fallCounter = 0;
	}
}


//**************************************************************************
// Handles movement down
//**************************************************************************
void Mario::handleDownMovement(){
	if (!onLadder && !onLadderDown) {	// Down only on ladder
		return;
	}
	else if (onFloor && !onLadderDown) {	// Down on floor when cant
		return;
	}
	else {	// go Down the ladder
		ladderGoingDown = true;
		ladderGoingUp = false;
		setDir(gameConfig::STAY);
		fallCounter = 0;
	}
}


//**************************************************************************
// Handles Mario's movement - updates win and death
//**************************************************************************
void Mario::move() {

	updateState();

	if (alive) {
		marioFall();			// Movement
		marioClimbsLadder();
		marioGoingDownLadder();
		marioJump();
		moveSides();
	}
	
	checkCollisions();	// Check barrel hit
	checkHitFloorDamage();	// Check if Mario should die from falling
	checkHammerCollected();

	isWin();	// Check if Mario won
}


//**************************************************************************
// Handles mario movement to right and left
//**************************************************************************
void Mario::moveSides(){

	Point newXY = getNextPoint();

	if (!(pBoard->isOnBoard(newXY))) {	// To not overflow from board
		setDir(gameConfig::STAY);
		newXY = getXY();
	}

	if (pBoard->isFloor(newXY)) { // Can't go through floor
		newXY = getXY();
	}

	Entity::move();
}


//**************************************************************************
// Checks and updates if Mario is on the floor
//**************************************************************************
bool Mario::isMarioOnFloor() {
	if (pBoard->isOnFloor(getXY())) {
		return onFloor = true;
	}
	else {
		return onFloor = false;
	}
}


//**************************************************************************
// Checks if Mario is hit by a barrel and updates his status
//**************************************************************************
void Mario::checkCollisions(){
	if (alive) {
		if (pBoard->getCharFromCurr(getXY()) == gameConfig::BARREL_CH) {
			pBoard->renderExplosion(getXY());
			killMario();
		}
		if(pBoard->getCharFromCurr(getXY()) == gameConfig::GHOST_CH) {
			killMario();
		}
		if (pBoard->getCharFromCurr(getXY()) == gameConfig::GHOST_CLIMB_LADDER_CH) {
			killMario();
		}
	}
}


//**************************************************************************
// Checks if Mario should die from falling
//**************************************************************************
void Mario::checkHitFloorDamage(){
	if (onFloor && alive) {
		if (fallCounter >= gameConfig::MARIO_MAX_FALL) {
			killMario();
			fallCounter = 0;
		}
		else {
			fallCounter = 0;
		}
	}
}


//**************************************************************************
// Checks if Mario has won the game
//**************************************************************************
void Mario::isWin(){
	if (pBoard->getCharFromOrig(getXY()) == gameConfig::PRINCESS_CH) {
		win = true;
	}
}


//**************************************************************************
// Handles Mario climbing up a ladder
//**************************************************************************
void Mario::marioClimbsLadder(){
	if (ladderGoingUp && onLadder) {
		if (pBoard->isFloor(getXY())) {
			setDir(gameConfig::STAY);
			ladderGoingUp = false;
		}
		Entity::move(0, -1, true);		// Move also through floor
		updateState();
	}
	else {
		ladderGoingUp = false;
	}
}


//**************************************************************************
// Handles Mario climbing down a ladder
//**************************************************************************
void Mario::marioGoingDownLadder() {

	if (ladderGoingDown && (onLadder || onLadderDown)) {
		Entity::move(0, 1, true);	// Move also through floor
		isMarioOnFloor();			// Update status

		if (onFloor) {	// Reached floor
			setDir(gameConfig::STAY);
			ladderGoingDown = false;
		}
	}
	else {
		ladderGoingDown = false;
	}
}


//**************************************************************************
// Checks if mario overlapped the hammer
//**************************************************************************
void Mario::checkHammerCollected(){
	if (pBoard->getCharFromOrig(getXY()) == gameConfig::HAMMER_CH) {
		hasHammer = true;
		pBoard->setHammerCollected();
		pBoard->setCharOnCurr(getXY(), ' ');
	}
}


//**************************************************************************
// Updates Mario
// erase, move, draw
//**************************************************************************
void Mario::updateMario(){
	checkCollisions();	// Check enemy hit
	eraseMario();
	move();
	draw();
}


//**************************************************************************
// Checks if Mario is on a ladder and updates his status
// Regarding floor above a ladder as a ladder
//**************************************************************************
bool Mario::isOnLadder(){
	if (Entity::isOnLadder()) {
		return onLadder = true;
	}
	else {
		return onLadder = false;
	}
}


//**************************************************************************
// Checks if Mario is on a ladder going down
//**************************************************************************
bool Mario::isOnLadderDown(){
	if (Entity::isOnLadderDown()) {
		return onLadderDown = true;
	}
	else {
		return onLadderDown = false;
	}
}


//**************************************************************************
// Handles Mario's fall
//**************************************************************************
void Mario::marioFall(){
	
	if (jumpTimer == 0 && !onFloor && !onLadder) {	// Not in jump and not on floor and not on ladder
		moveDown();						// Make mario fall
		fallCounter++;					// Update his fall counter

		updateState();
	}

}


//**************************************************************************
// Handles Mario jumps
//**************************************************************************
void Mario::marioJump(){
	if (jumpTimer > 0) {	// jumping go up
		if (pBoard->isOnBoard(getXY().above())) {
			if (!pBoard->isFloor(getXY().above())) {
				moveUp();
				jumpTimer--;
			}
			if (pBoard->isOnBoard(getXY().above())) {
				if(pBoard->isFloor(getXY().above())){
					jumpTimer = 0;
				}
			}
		}
		else {
			jumpTimer = 0;
		}
	}
}

