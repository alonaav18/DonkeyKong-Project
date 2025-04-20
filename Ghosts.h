#pragma once
#include "gameConfig.h"
#include "Board.h"
#include "Point.h"
#include "Enemy.h"


class Ghosts : public Enemy {

protected:
    Board* pBoard = nullptr;    // Board

public:
    Ghosts(Board* board) // Constructor - assuming donkey Kong is on board
        : Enemy(board, gameConfig::GHOST_CH),
        pBoard(board)
    {}
    virtual ~Ghosts() { }

    void randomizeDirection(int index);

    void updateGhosts();
    void activateGhosts();
    void resetGhosts();
    void eraseGhosts();

    // movement
    void setRandomDir(int index);
    bool checkDirValid(int index);
    void updateDirection(int index);
    int findGhostInPoint(const Point position) const;
    bool findAndKillGhostInPoint(const Point position);
    virtual void moveGhost(int index);
    void drawGhosts();
    void drawGhost(int index);
    void eraseGhost(int index) { eraseEntity(index); }
    void deleteGhost(int index) { deleteEntity(index); }
    void deleteAllGhosts() { removeAllEntities(); }
};