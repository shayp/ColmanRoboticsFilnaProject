#ifndef MAP_UTILS_H
#define MAP_UTILS_H
#include <string>
#include <vector>

#include "../CoreLib/Map.h"
#include "../CoreLib/Cell.h"

using namespace std;
using namespace CoreLib;

#define IMAGE_COLOR_CLEAR 255 // WHITE
#define IMAGE_COLOR_OBSTACLE 0 // BLACK

namespace Utils
{
	class MapUtils
	{
		public:
			static Map* pngToMap(string pngMapPath, float pixelsPerGridResolution);
			static void mapToPng(const Map& map, float pixelsPerGridResolution, string pngMapPath);
			static Map* blowUpMap(const Map& map, float robotMaxDimensionCm, float resolution);
			static void addMapWeights(Map* map);

		private:
			static unsigned getCellImageColor(unsigned row, unsigned col, const vector<unsigned char>& rawImage,
											  unsigned imageWidth, unsigned imageHeight, unsigned pixelsPerOneGrid);
			static void initMapFromImage(Map* map, vector<unsigned char>& rawImage, unsigned imageWidthPx,
										 unsigned imageHeightPx, unsigned pixelsPerOneGrid);

			static bool isCellNearWall(Cell* cell);
	};
}
#endif MAP_UTILS_H
