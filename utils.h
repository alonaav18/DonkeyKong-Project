#pragma once

#include <iostream>
#include <windows.h>
#include <chrono>

#include "gameConfig.h"
#include "Point.h"


void ShowConsoleCursor(bool showFlag);
static long getRandomSeed(){ return static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count()); }
void gotoxy(const Point& p);

void setConsoleColor(int color = gameConfig::DEFAULT_COLOR);

void printScreen(const char* const* screen, int color = gameConfig::DEFAULT_COLOR);
static void clearScreen(){system("cls");}