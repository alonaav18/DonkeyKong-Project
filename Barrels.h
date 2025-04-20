#pragma once
#include "Point.h"
#include "Board.h"
#include "Mario.h"
#include "Enemy.h"
#include "gameConfig.h"


class Barrels : public Enemy{

    Board* pBoard = nullptr;	        // Board
    Mario* pMario = nullptr;            // Mario

    Point spawnLocation = Point::NOT_FOUND;        // Searching for donkey Kong in the constructor
    int newBarrelTimer = gameConfig::NEW_BARREL_TIMER;  // releasing barrel timer
    std::vector<int> explodeTimer;

public:
    Barrels(Board* board, Mario* mario) // Constructor - assuming donkey Kong is on board
        : Enemy(board, gameConfig::BARREL_CH),
        pMario(mario),
        pBoard(board)
    {}


    // Main updating function
    void updateBarrels();


    // New barrels
    void releaseBarrel();
    void createNewBarrel();


    // Logic
    bool isFalling(int index) const;
    bool checkExplosion(int index);
    void updateDirection(int index);


    // Movement
    void fall(int index);
    void moveBarrel(int index);
    void drawBarrels();


    // Clearing barrels
    void resetBarrels();
    void eraseBarrel(int index);
    void eraseAllBarrels();


    int findBarrelInPoint(const Point position) const;
    bool findAndKillBarrelInPoint(const Point& position);
    void deleteBarrel(int index) { explodeTimer.erase(explodeTimer.begin() + index); deleteEntity(index); }
    void deleteAllBarrels();
    
    // BONUS
    void barrelExplode(int index);
};

