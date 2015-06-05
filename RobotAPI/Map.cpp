#include "Map.h"

Map::Map()
{
	for (int i = 0; i < Helper::MAP_ROWS ; i++)
	{
		for (int j = 0; j < Helper::MAP_COLUMNS ; j++)
		{
			_map[i][j] = Helper::UNKNOWN_CELL;
		}
	}
}

void Map::printMap()
{
	cout << "Printing Map: " << endl;
	for (int i = 0; i < Helper::MAP_ROWS ; i++)
	{
		for (int j = 0; j < Helper::MAP_COLUMNS ; j++)
		{
			// ░ ▒ ▓
			if (_map[i][j] == Helper::FREE_CELL)
			{
				cout << " ";
			}
			else if (_map[i][j] == Helper::OCCUPIED_CELL)
			{
				cout << "▓";
			}
			else
			{
				cout <<"░";
			}

			//cout << _map[i][j];
		}
		cout << endl;
	}
}

int Map::calculateXIndex(int x)
{
	return (x / Helper::MAP_RESOLUTION) + (Helper::MAP_COLUMNS / 2);
}

int Map::calculateYIndex(int y)
{
	return (y / Helper::MAP_RESOLUTION) - (Helper::MAP_ROWS / 2);
}

void Map::getMapCoordinates(double realX,double realY,int &mapX,int &mapY)
{
	mapX = calculateXIndex(realX);
	mapY = calculateYIndex(realY);
}

void Map::setCellValue(int x, int y, int value)
{
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	_map[xIndex][yIndex] = value;
}

int Map::getCellValue(int x, int y)
{
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	return _map[xIndex][yIndex];
}
