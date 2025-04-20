#pragma once
#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>

#include "gameConfig.h"
#include "utils.h"
#include "Point.h"


class Board {
	bool specialMode = false;
	const std::string currentFilename;
	bool hammerCollected = false;
	bool print = true;

	bool validBoard = true;
	Point startingMarioPoint = Point::NOT_FOUND;
	Point startingDonkeyPoint = Point::NOT_FOUND;
	Point PrincessPoint = Point::NOT_FOUND;
	Point marioPoint = Point::NOT_FOUND;

	bool widthTooShort = false;
	bool heightTooShort = false;
	bool invalidChars = false;

	Point legendPoint = Point::ZERO_POINT;

	char currentBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1] = {{}}; // +1 for null terminator
	char originalBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1] = {{}};


public:
	Board(bool specialMode_, const std::string filename) : specialMode(specialMode_), currentFilename(filename) {
	}

	// Load - reset - update
	bool load(const std::string& filename);
	void reset();
	void updateCurrent();
	void resetStage();
	void updateCharacter(char c, int col, int row);

	// Print
	void printCurrentBoard() const;
	void printOriginalBoard() const;
	void printChar(const Point& p, char ch, int color = gameConfig::DEFAULT_COLOR) const;
	void printLegend(int lives, int score, bool hasHammer);


	// Setter
	void eraseCharFromCurr(const Point& p);
	void setHammerCollected() { hammerCollected = true; };
	void setHammerLost() { hammerCollected = false; };
	void setCharOnCurr(const Point& p, char ch);
	void setPrintOff() { print = false; };
	void setPrintOn() { print = true; };
	void setMarioPoint(Point pos) { marioPoint = pos; };


	// Getter
	char getCharFromOrig(const Point& p) const { return originalBoard[p.getY()][p.getX()]; }
	char getCharFromCurr(const Point& p) const { return currentBoard[p.getY()][p.getX()]; }
	Point getStartingMarioPoint() const { return startingMarioPoint; }
	Point getStartingPrincessPoint() const { return PrincessPoint; }
	Point getStartingDonkeyPoint() const { return startingDonkeyPoint; }
	bool getWidthTooShort() const { return widthTooShort; }
	bool getHeightTooShort() const { return heightTooShort; }
	bool getInvalidChars() const { return invalidChars; }
	bool getValidBoard() const { return validBoard; }
	bool isOnFloor(const Point& p) const;
	bool isFloor(const Point& p) const;
	Point findCharacter(char ch, int occurrence = 1) const;
	bool isLadder(const Point& p) const {
		return (getCharFromOrig(p) == gameConfig::LADDER_CH);
	}
	bool isWall(const Point& p) const { return (getCharFromCurr(p) == gameConfig::WALL_CH);}
	bool isEnemyInPoint(Point xy) const {
		return (getCharFromCurr(xy) == gameConfig::GHOST_CH || getCharFromCurr(xy) == gameConfig::BARREL_CH || getCharFromCurr(xy) == gameConfig::GHOST_CLIMB_LADDER_CH);
	}
	bool isOnBoard(const Point& p) const {
		return (!isOverflow(p)) ? !isWall(p) : false;
	}
	bool isOverflow(const Point& p) const { 
		return (p.getX() >= gameConfig::GAME_WIDTH || p.getX() < 0 || p.getY() >= gameConfig::GAME_HEIGHT || p.getY() < 0);
	}
	bool getPrintMode() const { return print; }
	Point getMarioPoint() { return marioPoint; };



	// Bonus
	int getColorForChar(char c) const;
	void renderExplosion(Point location) const;
	void renderHammerHit(const Point& position);
};