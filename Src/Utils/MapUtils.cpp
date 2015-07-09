#include "MapUtils.h"
#include "../../Libs/PngLoader/lodepng.h"
#include "PngUtils.h"

#include <iostream>
#include <math.h>

using namespace Utils;
using namespace std;
using namespace CoreLib;

Map* MapUtils::pngToMap(string pngMapPath, float pixelsPerGridResolution)
{
	vector<unsigned char> rawImage;
	unsigned widthInPixels, heightInPixels;

	cout << "Trying to decode the map" << endl;

	unsigned error = lodepng::decode(rawImage, widthInPixels, heightInPixels, pngMapPath.c_str());

	if (error)
	{
		cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
	}

	Map* map = new Map((int)floor(heightInPixels / pixelsPerGridResolution),
				  (int)floor(widthInPixels / pixelsPerGridResolution));
	initMapFromImage(map, rawImage, widthInPixels, heightInPixels, pixelsPerGridResolution);

	return map;
}

void MapUtils::mapToPng(Map* map, float pixelsPerGridResolution, string pngMapPath)
{
	vector<unsigned char> rawImage;
	unsigned wayPointType;
	unsigned width = (unsigned)floor(map->getCols() * pixelsPerGridResolution);
	unsigned height = (unsigned)floor(map->getRows() * pixelsPerGridResolution);
	rawImage.resize(width * height * 4);

	int flooredResolution = (int)floor(pixelsPerGridResolution);

	cout << "The Matrix size" << width * height * 4 << endl;
	cout << "Rows: " << map->getRows() << "Cols: " << map->getCols() << endl;
	for (unsigned row = 0; row < map->getRows(); row++)
	{
		for (unsigned col = 0; col < map->getCols(); col++)
		{
			Cell* cell = map->getCell(row, col);
			unsigned char rPixel, gPixel, bPixel;
			unsigned char aPixel = 255;

			if (cell->Cost == COST_FREE_TO_GO)
			{
				rPixel = gPixel = bPixel = IMAGE_COLOR_CLEAR;
			}
			else if (cell->Cost == COST_OBSTICALE )
			{
				// Black color
				rPixel = gPixel = bPixel = IMAGE_COLOR_OBSTACLE;
			}
			else if(cell->Cost == COST_NEAR_WALL)
			{
				// Gray color
				rPixel = gPixel = bPixel = IMAGE_COLOR_NEAR_WALL;
			}
			else if(cell->Cost == COST_NEAR_WALL_SECOND)
			{
				// Red color, close to wall
				rPixel = 201;
				gPixel = 14;
				bPixel = 14;
			}
			else if(cell->Cost == COST_NEAR_WALL_THIRD)
			{
				// Orange, close to wall less walls
				rPixel = 236;
				gPixel = 119;
				bPixel = 41;
			}
			else if(cell->Cost == COST_SECOND_LEVEL)
			{
				// Yellow, close to near walls
				rPixel = 201;
				gPixel = 201;
				bPixel = 14;
			}

			wayPointType = cell->GetWayPointType();
			if(wayPointType == eAStarWayPoint)
			{
				rPixel = 15;
				gPixel = 192;
				bPixel = 202;
			}
			else if(wayPointType == ePathWayPoint)
			{
				rPixel = 169;
				gPixel = 69;
				bPixel = 189;
			}

			int basePos = (row * width + col) * 4 * flooredResolution;
			for (int i = 0; i < flooredResolution; i++)
			{
				for (int j = 0; j < flooredResolution; j++)
				{
					int offset = (i * width + j) * 4;

					rawImage[basePos + offset + 0] = rPixel;
					rawImage[basePos + offset + 1] = gPixel;
					rawImage[basePos + offset + 2] = bPixel;
					rawImage[basePos + offset + 3] = aPixel;
				}
			}
		}
	}

	unsigned error = lodepng::encode(pngMapPath, rawImage, width, height);

	if (error)
	{
		cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
	}
}

Map* MapUtils::blowUpMap(const Map& map, float robotMaxDimensionCm, float resolution)
{
	Map* blownMap = new Map(map);

	// Blow up by more than needed (ceiling), just in case
	int blowCellsOneSide = (int)floor(0.5 * robotMaxDimensionCm * resolution) / 2;

	for (int row = 0; row < (int)map.getRows(); row++)
	{
		for (int col = 0; col < (int)map.getCols(); col++)
		{
			Cell* originalCell = map(row, col);
			if (!originalCell->isCellWalkable())
			{
				for (int i = -blowCellsOneSide; i < blowCellsOneSide; i++)
				{
					for (int j = -blowCellsOneSide; j < blowCellsOneSide; j++)
					{
						Cell* cellToBlow = (*blownMap)(row + i, col + j);
						if (cellToBlow != NULL/* && !cellToBlow->isWalkable()*/)
						{
							cellToBlow->Cost = originalCell->Cost;
						}
					}
				}
			}
		}
	}

	return blownMap;
}

unsigned MapUtils::getCellImageColor(unsigned row, unsigned col, const vector<unsigned char>& rawImage,
									 unsigned imageWidth, unsigned imageHeight, unsigned pixelsPerOneGrid)
{
	for (unsigned i = 0; i < pixelsPerOneGrid; i++)
	{
		for (unsigned j = 0; j < pixelsPerOneGrid; j++)
		{
			unsigned char color = PngUtils::getPixelColor(rawImage, imageWidth, imageHeight,
														  row * pixelsPerOneGrid + i, col * pixelsPerOneGrid + j);
			if (color == IMAGE_COLOR_OBSTACLE)
			{
				return IMAGE_COLOR_OBSTACLE;
			}
		}
	}
	return IMAGE_COLOR_CLEAR;
}

void MapUtils::initMapFromImage(Map* map, vector<unsigned char>& rawImage, unsigned imageWidthPx,
							    unsigned imageHeightPx, unsigned pixelsPerOneGrid)
{
	for (unsigned row = 0; row < map->getRows(); row++)
	{
		for (unsigned col = 0; col < map->getCols(); col++)
		{
			Cell* cell = (*map)(row, col);

			unsigned cellColor = getCellImageColor(row, col, rawImage, imageWidthPx, imageHeightPx, pixelsPerOneGrid);
			if (cellColor == IMAGE_COLOR_OBSTACLE)
			{
				cell->Cost = COST_OBSTICALE;
			}
			else if (cellColor == IMAGE_COLOR_CLEAR)
			{
				cell->Cost = COST_FREE_TO_GO;
			}
		}
	}
}

void MapUtils::addMapWeights(Map* map)
{
	unsigned counter  = 0;
	for (unsigned row = 0; row < map->getRows(); row++)
	{
		for (unsigned col = 0; col < map->getCols(); col++)
		{
			Cell* cell = (*map)(row, col);
			if (cell->isCellWalkable() )
			{
				counter = GetNumOfWallNeighbours(cell);
				if (counter >= 1 && counter <= 3)
				{
					cell->Cost = COST_NEAR_WALL_THIRD;

				}
				else if (counter >= 4 && counter <= 6)
				{
					cell->Cost = COST_NEAR_WALL_SECOND;
				}
				else if (counter > 6)
				{
					cell->Cost = COST_NEAR_WALL;
				}
			}
		}
	}

	for (unsigned row = 0; row < map->getRows(); row++)
	{
		for (unsigned col = 0; col < map->getCols(); col++)
		{
			Cell* cell = (*map)(row, col);
			SetSecondLevel(cell);
		}
	}
}

unsigned MapUtils::GetNumOfWallNeighbours(Cell* cell)
{
	unsigned counter = 0;
	for (Cell* neighborCell : cell->getNeighbors())
	{
		if (neighborCell != NULL && !neighborCell->isCellWalkable())
		{
			counter++;
		}
	}

	return counter;
}

void MapUtils::SetSecondLevel(Cell* cell)
{
	for (Cell* neighborCell : cell->getNeighbors())
	{
		if (neighborCell != NULL &&
			cell->Cost == COST_FREE_TO_GO
			&& neighborCell->Cost > COST_SECOND_LEVEL)
		{
			cell->Cost = COST_SECOND_LEVEL;
		}
	}
}
