#pragma once

#include "Point.h"
#include "Board.h"
#include "gameConfig.h"


class Entity {
	Board* pBoard = nullptr;
	char ch;
	Point spawnPoint = Point::NOT_FOUND;
	Point xy = Point::NOT_FOUND;
	gameConfig::Direction dir;
	int color = gameConfig::DEFAULT_COLOR;


public:
	Entity(Board* pBoard_, char ch_, const Point& spawnPoint, gameConfig::Direction dir_ = gameConfig::STAY)
		:pBoard(pBoard_), ch(ch_), spawnPoint(spawnPoint), dir(dir_)
	{
		xy = spawnPoint;
	}

	// Actions
	bool move(bool throughFloor = false);
	bool move(int xOffset, int yOffset, bool throughFloor = false);

	bool moveDown() { return move(0, 1); }
	bool moveUp() { return move(0, -1); }
	bool moveLeft() { return move(-1, 0); }
	bool moveRight() { return move(1, 0); }
	void reset() { xy = spawnPoint; dir = gameConfig::STAY; }
	void draw() { pBoard->setCharOnCurr(xy, ch); }
	void erase() { pBoard->eraseCharFromCurr(xy); }
	void update() { erase(); move(); draw(); }
	void reverseDir() { dir.x *= -1; dir.y *= -1; }

	// Setters
	void setDir(const gameConfig::Direction& dir_){ dir = dir_; }
	void setColor(int color_) { color = color_; }
	void setXY(const Point& xy_) { xy = xy_; }
	void setChar(char ch_) { ch = ch_; }	
	bool isOnFloor() const{ return pBoard->isOnFloor(xy); }
	bool isOnLadder() const;
	bool isOnLadderDown() const;
	void setSpawnPoint(const Point& spawnPoint_) { spawnPoint = spawnPoint_; }


	// Getters
	char getCh() const { return ch; }
	Point getXY() const { return xy; }
	Point getNextPoint() const {return xy.copyWithOffset(dir.x, dir.y); }
	gameConfig::Direction getDir() const { return dir; }
	int getColor() const { return color; }
	Point getPointBelow() const { return xy.below(); }
	Point getPointAbove() const { return xy.above(); }
	Point getNextPos() const { return xy.copyWithOffset(dir.x, dir.y); }
	Point getSpawnPoint() const { return spawnPoint; }
};