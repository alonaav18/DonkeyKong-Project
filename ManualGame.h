#pragma once
#include "Game.h" 

class ManualGame : public Game{
	bool saveMode;

public:
	ManualGame(bool saveMode_, bool specialMode_, std::vector<std::string> filenames_, int index_)
		:saveMode(saveMode_), Game(specialMode_, filenames_, index_) 
	{
		setRandomSeed(getRandomSeed());
	}

	~ManualGame() {}

	void updateSteps() override { if (saveMode) { saveScreenSteps(); } setRandomSeed(getRandomSeed()); }
	void updateResults() override { if (saveMode) { addScoreToResult(); saveScreenResults(); } }
	void getInput() override;
	void updateDeathResult() override { addDeathToResult(); }

	void marioDied() override { resetGameStage(); addDeathToResult(); }
	void finishedScreen(bool screenWon) override { screenWon ? addWinToResult() : addDeathToResult(); }
};

