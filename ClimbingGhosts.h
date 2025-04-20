#pragma once
#include "Ghosts.h"


class ClimbingGhosts : public Ghosts {
	

public:
	ClimbingGhosts(Board* board) : Ghosts(board) { setChar(gameConfig::GHOST_CLIMB_LADDER_CH); }
	void moveGhost(int index) override;


};

