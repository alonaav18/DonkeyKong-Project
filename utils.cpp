#include "utils.h"


//**************************************************************************
// Setting console printing color to given color
// Resetting to default if not given
//**************************************************************************
void setConsoleColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


//**************************************************************************
// clears and prints to screen as lines
// Accepts color for the whole print, otherwise set to default
//**************************************************************************
void printScreen(const char* const* screen, int color){

    setConsoleColor(color);
    clearScreen();

    for (int i = 0; i < gameConfig::GAME_HEIGHT - 1; i++) {
        std::cout << screen[i] << '\n';
    }
    std::cout << screen[gameConfig::GAME_HEIGHT - 1];
}



//**************************************************************************
// Sets the printing curser on the specified point 
//**************************************************************************
void gotoxy(const Point& p) { 
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = (short)p.getX(); // Set the X coordinate
    coord.Y = (short)p.getY(); // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}



//**************************************************************************
// Shows/Hides the console printing cursor
//**************************************************************************
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}