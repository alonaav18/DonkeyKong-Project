#pragma once
#include <iostream>
//#include "gameConfig.h"

class Point {

	int x, y;

public:
	static const Point NOT_FOUND;
	static const Point ZERO_POINT;

	Point(int _x, int _y) : x(_x), y(_y) {}

	void setXY(int _x, int _y) { x = _x; y = _y; }

	int getX() const { return x; }
	int getY() const { return y; }

	void setOffset(int xOffset, int yOffset) { x += xOffset; y += yOffset; }
	Point copyWithOffset(int xOffset, int yOffset) const { return Point(x + xOffset, y + yOffset); }

	void goUp() { y -= 1; }
	void goDown() { y += 1; }

	const Point above() const { return Point(x, y - 1); }
	const Point below() const { return Point(x, y + 1); }

	bool operator==(const Point& other) const { return x == other.x && y == other.y; }
	bool operator!=(const Point& other) const { return !(*this == other); }

	double distance(const Point& other) const { return std::sqrt(( x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
};