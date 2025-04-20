#include "Menu.h"


int main(int argc, char** argv) {

	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";

	if (isSilent) {
		Menu().startSilent();
	}
	else if (isLoad) {
		Menu().startLoad();
	}
	else {
		Menu(isSave).startMenu(); //	Showing start menu
	}
}
