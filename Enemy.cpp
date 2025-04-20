#include "Enemy.h"


//**************************************************************************
// Adds entity to enemy
//**************************************************************************
void Enemy::addEntity(const Point& spawnPoint, gameConfig::Direction dir){
	entities.push_back(Entity(pBoard, ch, spawnPoint, dir));
}


//**************************************************************************
// Returns index in the vector or not found
//**************************************************************************
int Enemy::findEntity(const Point& xy){
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i].getXY() == xy) {
			return i;
		}
	}
	return gameConfig::NOT_FOUND;
}


//**************************************************************************
// Finds entity in point and deletes
//**************************************************************************
void Enemy::findAndKillEntity(const Point& xy){
	deleteEntity(findEntity(xy));
}


//**************************************************************************
// Deletes all entities from vector
//**************************************************************************
void Enemy::removeAllEntities(){
	while (entities.size() > 0) {
		deleteEntity(0);
	}
}


//**************************************************************************
// Moves all the entities
//**************************************************************************
void Enemy::moveEntities(){
	for (int i = 0; i < entities.size(); i++) {
		entities[i].move();
	}
}


//**************************************************************************
// Updates all entities
//**************************************************************************
void Enemy::updateEntities(){
	for (int i = 0; i < entities.size(); i++) {
		entities[i].update();
	}
}


//**************************************************************************
// Draws all entities
//**************************************************************************
void Enemy::drawEntities(){
	for (int i = 0; i < entities.size(); i++) {
		entities[i].draw();
	}
}


//**************************************************************************
// Erases all entities
//**************************************************************************
void Enemy::eraseEntities(){
	for (int i = 0; i < entities.size(); i++) {
		eraseEntity(i);
	}
}


//**************************************************************************
// Moves a specific entity 
//**************************************************************************
bool Enemy::moveEntity(int index, bool throughWalls){
	return entities[index].move(throughWalls);
}


//**************************************************************************
// Deletes an entity in the index
//**************************************************************************
void Enemy::deleteEntity(int index){	// Not clearing board
	entities[index].erase();
	entities.erase(entities.begin() + index);
}


//**************************************************************************
// Resets entities
//**************************************************************************
void Enemy::resetEntities(){
	for (int i = 0; i < entities.size(); i++) {
		entities[i].reset();
	}
}
