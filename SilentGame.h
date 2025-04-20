#pragma once
#include "AutomaticGame.h"


class SilentGame : public AutomaticGame{

public:
	SilentGame(bool specialMode_, std::vector<std::string> filenames_, int index_)
		:AutomaticGame(specialMode_, filenames_, index_)
	{
		setGameSpeed(gameConfig::GAME_SPEED_SILENT);
		getBoard().setPrintOff();
	}
	~SilentGame() {
		clearScreen();
	}

	void updateResults() override { loadScreenResults(); }
	void marioDied() override;
	void finishedScreen(bool screenWon) override;
	void updateDeathResult() override;


	void printEndGame(bool win) const override {}	// Do nothing
	void printGame() override {}	// FIX GET FROM BOARD
};

