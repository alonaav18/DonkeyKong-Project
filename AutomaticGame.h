#pragma once
#include "Game.h"

class AutomaticGame : public Game{

public:
	AutomaticGame(bool specialMode_, std::vector<std::string> filenames_, int index_)
		:Game(specialMode_, filenames_, index_)
	{
		setGameSpeed(gameConfig::GAME_SPEED_LOAD);
	}
	
	void updateSteps() override { loadScreenSteps(); };
	void updateDeathResult() override {}

	void getInput() override;
	void updateResults() override {}
	void marioDied() override { resetGameStage(); }
	void finishedScreen(bool screenWon) override {}
};