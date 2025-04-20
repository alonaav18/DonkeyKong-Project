#include "Board.h"

//**************************************************************************
// Loads a board from screen
//**************************************************************************
bool Board::load(const std::string& filename) {
	reset();

	validBoard = true;

	std::ifstream screen_file(filename);	// Opens file
	if(!(screen_file.is_open())){
		validBoard = false;
		return validBoard;
	}
	int curr_row = 0;
	int curr_col = 0;
	char c;


	while (!screen_file.get(c).eof() && curr_row < gameConfig::GAME_HEIGHT) {	// Reads untill the EOF or filled all rows
		if (c == '\n') {
			if (curr_col < gameConfig::GAME_WIDTH) {	// If the row is too short
				validBoard = false;
				widthTooShort = true;
				break;
			}
			++curr_row;
			curr_col = 0;
			continue;
		}

		else if (curr_col < gameConfig::GAME_WIDTH) {
			if (c >= 32 && c <= 126) {	// Printables values
				updateCharacter(c, curr_col, curr_row);
				if (c == gameConfig::LEGEND_CH) {	// Not printing the legend char- only for location
					originalBoard[curr_row][curr_col++] = ' ';
				}
				else {
					originalBoard[curr_row][curr_col++] = c;
				}
			}
			else{	// invalid chars
				invalidChars = true;
				validBoard = false;
				break;
			}
			if(curr_col == gameConfig::GAME_WIDTH){	// End of row
				originalBoard[curr_row][curr_col] = '\0';
			}
		}
	}

	if(validBoard && curr_row < gameConfig::GAME_HEIGHT){
		heightTooShort = true;
		validBoard = false;
	}

	if (validBoard){
		if(startingDonkeyPoint == Point::NOT_FOUND || startingMarioPoint == Point::NOT_FOUND || PrincessPoint == Point::NOT_FOUND){
			validBoard = false;
		}
		else {
			resetStage();
		}
	}

	return validBoard;
}


//**************************************************************************
// resets all stage specific variables
//**************************************************************************
void Board::reset() {
	startingDonkeyPoint = Point::NOT_FOUND;
	startingMarioPoint = Point::NOT_FOUND;
	PrincessPoint = Point::NOT_FOUND;
	legendPoint = Point::ZERO_POINT;
	setHammerLost();
}


//**************************************************************************
// Resetting the current board to the original board
//**************************************************************************
void Board::updateCurrent(){
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], gameConfig::GAME_WIDTH + 1);
	}
}


//**************************************************************************
// checks if char is for character
//**************************************************************************
void Board::updateCharacter(char c, int col, int row){
	switch (c) {
		case gameConfig::MARIO_CH:
			startingMarioPoint = Point(col, row);
			break;
		case gameConfig::DONKEY_CH:
			startingDonkeyPoint = Point(col, row);
			break;
		case gameConfig::PRINCESS_CH:
			PrincessPoint = Point(col, row);
			break;
		case gameConfig::LEGEND_CH:
			legendPoint = Point(col, row);
			break;
	}
}


//**************************************************************************
// If special mode is not activated - returning default color
// Otherwise returning char's predefined color 
//**************************************************************************
int Board::getColorForChar(char c) const{
	if (!specialMode) {
		return gameConfig::DEFAULT_COLOR;
	}

	switch (c) {
		case gameConfig::FLOOR_STRAIGHT_CH: return gameConfig::STRAIGHT_FLOOR_COLOR;
		case gameConfig::MARIO_CH: return gameConfig::MARIO_COLOR;
		case gameConfig::PRINCESS_CH: return gameConfig::PRINCESS_COLOR;
		case gameConfig::DONKEY_CH: return gameConfig::DONKEY_COLOR;
		case gameConfig::BARREL_CH: return gameConfig::BARRELS_COLOR;
		case gameConfig::LADDER_CH: return gameConfig::LADDER_COLOR;
		case gameConfig::FLOOR_RIGHT_CH: return gameConfig::DEFAULT_COLOR;
		case gameConfig::FLOOR_LEFT_CH: return gameConfig::DEFAULT_COLOR;

		default: return gameConfig::DEFAULT_COLOR;   // Default (White)
	}
}

//**************************************************************************
// prints a char and sets of current boar
//**************************************************************************
void Board::setCharOnCurr(const Point& p, char ch){
	if (p != Point::NOT_FOUND) {
		currentBoard[p.getY()][p.getX()] = ch;
		printChar(p, ch, getColorForChar(ch));
	}
}

//**************************************************************************
// prints a char
//**************************************************************************
void Board::printChar(const Point& p, char ch, int color) const{
	if (!print) {return;}
	gotoxy(p);
	setConsoleColor(color);
	std::cout << ch;
}


//**************************************************************************
// Clearing the screen and prints current board
//**************************************************************************
void Board::printCurrentBoard() const{
	clearScreen();

	for (int y = 0; y < gameConfig::GAME_HEIGHT; ++y) {
		for (int x = 0; currentBoard[y][x] != '\0'; ++x) {
			printChar(Point(x, y), currentBoard[y][x], getColorForChar(currentBoard[y][x]));
		}
	}
}


//**************************************************************************
// Print the original board
//**************************************************************************
void Board::printOriginalBoard() const{
	clearScreen();

	for (int y = 0; y < gameConfig::GAME_HEIGHT; ++y) {
		for (int x = 0; originalBoard[y][x] != '\0'; ++x) {
			printChar(Point(x, y), originalBoard[y][x], getColorForChar(originalBoard[y][x]));
		}
	}
}


//**************************************************************************
// Resets a stage
//**************************************************************************
void Board::resetStage(){
	updateCurrent();
	setHammerLost();
}


//**************************************************************************
// Checks if point's char is floor
//**************************************************************************
bool Board::isFloor(const Point& p) const{
	return (!isOverflow(p) && (getCharFromOrig(p) == gameConfig::FLOOR_STRAIGHT_CH || getCharFromOrig(p) == gameConfig::FLOOR_RIGHT_CH || getCharFromOrig(p) == gameConfig::FLOOR_LEFT_CH));
}

//**************************************************************************
// Find a character on the original board - assuming one is on the board 
// If more than one char is present returning the first one it finds
// Occurrence is the number of the character on the board (occurrences)
//**************************************************************************
Point Board::findCharacter(char ch, int occurrence) const{
	int count = 0;

	for (int x = 0; x < gameConfig::GAME_WIDTH; x++) {
		for (int y = 0; y < gameConfig::GAME_HEIGHT; y++) {
			if (originalBoard[y][x] == ch) {
				count++;
				if (count == occurrence) {
					return Point(x, y);
				}
			}
		}
	}
	return Point::NOT_FOUND;
}


//**************************************************************************
// Renders an explosion with explosion radius around the given point - assuming board is cleared after
// BONUS points checks for special mode
// created with the help of AI
//**************************************************************************
void Board::renderExplosion(Point location) const{
	if (!specialMode || !print) return;
	
	setConsoleColor(gameConfig::EXPLOSION_COLOR);
	const int maxExplosionSize = gameConfig::BARREL_EXPLOAD_DISTANCE + 1; // Maximum size for half the explosion's side (final size = 2*maxExplosionSize - 1)
	const int centerX = location.getX();
	const int centerY = location.getY();

	for (int size = 1; size <= maxExplosionSize; ++size) {
		// Calculate bounds of the square explosion
		int left = max(centerX - size + 1, 0);
		int right = min(centerX + size - 1, gameConfig::GAME_WIDTH - 1);
		int top = max(centerY - size + 1, 0);
		int bottom = min(centerY + size - 1, gameConfig::GAME_HEIGHT - 1);

		// Render the explosion as a filled rectangle
		for (int y = top; y <= bottom; ++y) {
			for (int x = left; x <= right; ++x) {
				gotoxy(Point(x, y));
				std::cout << '*';
			}
		}

		// Delay for animation effect
		Sleep(gameConfig::EXPLOSION_ANIMATION_DELAY); // 200 ms delay
	}
}


//**************************************************************************
// Prints Mario's remaining lives - Assuming map is not present on the top left corner 
// Prints lives in color on special mode
// Not updating the current board
// Assumes L is in a valid point - might "overflow" from screen but not crash.
//**************************************************************************
void Board::printLegend(int lives, int score, bool hasHammer) {
	if(!print) return;

	gotoxy(legendPoint);


	// Lives
	gotoxy(legendPoint.copyWithOffset(0, 0));
	setConsoleColor(gameConfig::DEFAULT_COLOR);
	std::cout << "Lives= ";
	if (specialMode) {
		setConsoleColor(gameConfig::LEGEND_LIVES_COLOR);
	}
	for (int i = 0; i < lives; i++) {
		std::cout << "<3 ";
	}

	// Score
	gotoxy(legendPoint.copyWithOffset(0, 1));
	setConsoleColor(gameConfig::DEFAULT_COLOR);
	std::cout << "Score= ";
	if (specialMode) {
		setConsoleColor(gameConfig::LEGEND_SCORE_COLOR);
	}
	std::cout << score;
	
	
	// Hammer
	if (hasHammer) {
		if (specialMode) {
			setConsoleColor(gameConfig::HAMMER_COLOR);
		}
		gotoxy(legendPoint.copyWithOffset(0, 2));
		std::cout << "P";
	}
}


//**************************************************************************
// Bonus animation for hammer hit
//**************************************************************************
void Board::renderHammerHit(const Point& position){
	setCharOnCurr(position, '+');
	Sleep(300);
	eraseCharFromCurr(position);
}



//**************************************************************************
// Returns if a point is on the floor
// also returning true if the point below is not in game boundaries
//**************************************************************************
bool Board::isOnFloor(const Point& p) const {
	if (p.below().getY() > gameConfig::GAME_HEIGHT - 1) {
		return true;
	}
	if (isFloor(p.below())) {
		return true;
	}
	else {
		return false;
	}
}


//**************************************************************************
// Erasing a point from the current board to the original board
// Setting ' ' instead of Mario's original location
//**************************************************************************
void Board::eraseCharFromCurr(const Point& p){

	char defaultChar = getCharFromOrig(p);

	if (defaultChar == gameConfig::HAMMER_CH && hammerCollected) {
		setCharOnCurr(p, ' ');
	}
	else if (defaultChar == gameConfig::MARIO_CH || defaultChar == gameConfig::GHOST_CH || defaultChar == gameConfig::GHOST_CLIMB_LADDER_CH) {	// Original Mario starting location - replace with ' '
		setCharOnCurr(p, ' ');
	}
	else {
		setCharOnCurr(p, defaultChar);
	}
}
