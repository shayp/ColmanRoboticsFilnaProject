#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "Helper.h"

using namespace std;

class Map
{
	int _map[Helper::MAP_ROWS][Helper::MAP_COLUMNS];
	int calculateXIndex(int x);
	int calculateYIndex(int y);
public:
	Map();
	void getMapCoordinates(double realX,double realY,int &mapX,int &mapY);
	int getCellValue(int x, int y);
	void setCellValue(int x, int y, int value);
	void printMap();
};

#endif /* MAP_H_ */
