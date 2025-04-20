#pragma once

#include <iostream>

#include "gameConfig.h"
#include "utils.h"
#include "Board.h"
#include "Point.h"
#include "Entity.h"


class Mario : public Entity{


	char ch = gameConfig::MARIO_CH;
	Board* pBoard = nullptr;	// current board	

	bool win = false;
	int lives = gameConfig::MARIO_STARTING_LIVES;

	
	int hammerDirX = 1;	// Starting hammer on the right	

	bool falling = false;
	int fallCounter = 0;
	int jumpTimer = 0;	// How many more blocks left to increase

	bool onFloor = true;
	bool onLadder = false;
	bool onLadderDown = false;

	bool ladderGoingDown = false;
	bool ladderGoingUp = false;
	
	bool alive = true;
	bool hasHammer = false;

public:
	Mario(Board* board) : Entity(board, gameConfig::MARIO_CH, Point::NOT_FOUND), pBoard(board) {}

	void resetMario();
	void killMario() { lives--; alive = false;}
	
	// Movement
	bool keyPressed(char key);
	void updateMario();
	void move();
	void handleUpMovement();
	void handleDownMovement();
	void moveSides();
	void marioFall();
	void marioJump();
	void marioClimbsLadder();
	void marioGoingDownLadder();
	void checkHammerCollected();


	void eraseMario();
	void draw();

	// Logic
	void updateState() { isOnLadder(); isOnLadderDown(); isMarioOnFloor(); }
	void checkCollisions();
	bool isOnLadder();
	bool isOnLadderDown();
	bool isMarioOnFloor();
	void isWin();
	void checkHitFloorDamage();
	

	//Getters
	bool getHasHammer() const { return hasHammer; }
	Point getHammerPoint() const { return Point(getXY().getX() + hammerDirX, getXY().getY()); }

	int getLives() const { return lives; }
	bool winState() const {return win;}
	bool isAlive() const { return(alive); }
	//Point getMarioPoint() const{ return marioPoint; }
	int getHammerDirX() const{ return hammerDirX; }

	
	//Setters
	void makeAlive() { alive = true; }
};