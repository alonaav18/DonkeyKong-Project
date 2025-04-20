#pragma once

#include <vector>
#include "gameConfig.h"
#include "Board.h"
#include "Entity.h"


// An enemy holds and manages many entities

class Enemy{
	Board* pBoard;
	std::vector<Entity> entities;

	char ch;


public:
	Enemy(Board* pBoard_, char ch_): pBoard(pBoard_), ch(ch_){}
	
	void addEntity(const Point& spawnPoint, gameConfig::Direction dir);
	int findEntity(const Point& xy);
	void findAndKillEntity(const Point& xy);
	void removeAllEntities();
	void resetEntities();
	void moveEntities();
	void updateEntities();
	void eraseEntities();
	void setChar(char ch_) { ch = ch_; }
	char getChar() const { return ch; }

	int getEntitiesSize() const { return (int)(entities.size()); }
	void drawEntities();
	
	// Specific entity
	void drawEntity(int index) { entities[index].draw(); }
	void eraseEntity(int index) { entities[index].erase(); }
	bool moveEntity(int index, bool throughWalls = false);
	void climbLadderUpEntity(int index) { entities[index].move(0, -1, true); }
	void climbLadderDownEntity(int index) { entities[index].move(0, 1, true); }
	void moveEntityDown(int index) { entities[index].moveDown(); }
	void deleteEntity(int index);
	void setEntityDirection(int index, gameConfig::Direction dir) { entities[index].setDir(dir); }
	void reverseEntityDir(int index) { if (index != gameConfig::NOT_FOUND) { entities[index].reverseDir(); } }
	
	Point getEntityPoint(int index) const { return entities[index].getXY(); }
	bool isOnFloor(int index) const { return entities[index].isOnFloor(); }
	bool isOnLadder(int index) const { return entities[index].isOnLadder(); }
	bool isOnLadderDown(int index) const { return entities[index].isOnLadderDown(); }
	gameConfig::Direction getEntityDirection(int index) {return entities[index].getDir(); }


};

