#include "Menu.h"



//**************************************************************************
// Showing DONKEY KONG icon for PREMENU_TIME
//**************************************************************************
void Menu::showPreMenuScreen() const{
	printScreen(PREMENU);
	Sleep(gameConfig::PREMENU_TIME);
}



//**************************************************************************
// Showing instructions screen- waiting for key to go back to main menu
//**************************************************************************
void Menu::instructionsScreen() const{
	printScreen(INSTRUCTIONS);

	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (key == gameConfig::MENU_BACK_FROM_INSTRUCTIONS) {
				printMainMenu();
				break;
			}
		}
	}
}


//**************************************************************************
// Prints main menu
//**************************************************************************
void Menu::printMainMenu() const{
	printScreen(MENU);
	printSpecialMode();
}



//**************************************************************************
// Prints the special mode true or false on the main menu
//**************************************************************************
void Menu::printSpecialMode() const {
	gotoxy(Point(gameConfig::SPECIAL_MODE_X, gameConfig::SPECIAL_MODE_Y));
	std::cout << (specialMode ? "ON " : "OFF");

}




//**************************************************************************
// Starting the menu
//**************************************************************************
void Menu:: startMenu(){
	showPreMenuScreen();		// Donkey Kong icon screen
	mainMenu();					// Starting main menu
}



//**************************************************************************
// Showing main menu and waiting for user's input
// Handling win and lose screens
//**************************************************************************
void Menu::mainMenu(){
	printMainMenu();

	while (true) {
		if (_kbhit()) {
			char key = _getch();
			
			if (key == gameConfig::MENU_START_GAME) {
				if (filenames.size() > 0) {
					ManualGame(isSave,getSpecialMode(), filenames, gameConfig::START_SCREEN).run(); 
				}
				else {
					printScreen(NO_FILES_FOUND);
					Sleep(2000);
				}
				printMainMenu();				// Restarting menu
			}
			else if (key == gameConfig::MENU_SPECIAL_MODE) {
				toggleSpecialMode();
				printSpecialMode();
			}
			else if (key == gameConfig::MENU_START_FROM_FILE) {	// Starting game from file
				startFromFileScreen();
			}

			else if (key == gameConfig::MENU_SHOW_INSTRUCTIONS) {	// Instructions screen
				instructionsScreen();
			}

			else if (key == gameConfig::MENU_EXIT_GAME) {			// Exit game
				clearScreen();
				break;
			}
		}
	}
}



//**************************************************************************
// Showing a screen with files to choose from
//**************************************************************************
void Menu::startFromFileScreen(){
	int page = 0;

	printScreensPage(page);

	// Get answer
	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (key >= '0' && key <= '9') {
				if (page * gameConfig::MAX_FILES_IN_SCREEN + key - '0' < filenames.size()) {
					ManualGame(isSave, getSpecialMode(), filenames, page * gameConfig::MAX_FILES_IN_SCREEN + key - '0').run();
					printMainMenu();
					break;
				}
			}
			if(std::tolower(key) == gameConfig::MENU_NEXT_SCREEN) {
				if ((page+1) * gameConfig::MAX_FILES_IN_SCREEN < filenames.size()) {
					page++;
					printScreensPage(page);
				}
			}
			if (std::tolower(key) == gameConfig::MENU_BACK_SCREEN) {
				if (page > 0) {
					page--;
					printScreensPage(page);
				}
			}
			if (key == gameConfig::ESC) {
				printMainMenu();
				break;
			}
		}
	}

	printMainMenu();
}



//**************************************************************************
// Takes all the current screen files from the path
//**************************************************************************
void Menu::getAllBoardFilenames(std::vector<std::string>& vec_to_fill){

	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 5) == "dkong" && filename.extension() == ".screen") {
			vec_to_fill.push_back(filenameStr);
		}
	}
	std::sort(vec_to_fill.begin(), vec_to_fill.end());
}



//**************************************************************************
// Prints the screens page
//**************************************************************************
void Menu::printScreensPage(int page){
	printScreen(FILE_SELECT);
	Point curser(gameConfig::CHOOSE_FILE_LOC_X, gameConfig::CHOOSE_FILE_LOC_Y);
	bool printed = false;
	for (int i = 0; i < gameConfig::MAX_FILES_IN_SCREEN && (i + (page*gameConfig::MAX_FILES_IN_SCREEN)) < filenames.size(); i++) {
		printed = true;
		gotoxy(curser);
		std::cout << "(" << i << ")  ";
		int j = curser.getX() + 5;	// ^ number difference
		int nameSize = (filenames[page * gameConfig::MAX_FILES_IN_SCREEN + i].length());
		for (int p = 0; p < nameSize ; p++) {
			if (j+p >= gameConfig::GAME_WIDTH - 5) {
				std::cout << "...";
				break;
			}
			else {
				std::cout << filenames[page * gameConfig::MAX_FILES_IN_SCREEN + i][p];
			}
		}
		curser.setOffset(0, 2);
	}
	if(!printed) {
		gotoxy(curser);
		std::cout << "No files found";
	}
}
