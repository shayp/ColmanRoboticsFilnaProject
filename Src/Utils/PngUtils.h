#ifndef PNG_UTILS_H
#define PNG_UTILS_H
#include <vector>
#include <string>

using namespace std;

#define COLOR_BLACK 0
#define COLOR_WHITE 255
#define COLOR_INVALID -1

namespace Utils
{
	class PngUtils
	{
		public:
			static unsigned char getPixelColor(const vector<unsigned char>& rawImage, unsigned width, unsigned height, unsigned row, unsigned col);
			static void blowMap(string mapFilename, int numPixelsToBlow, string blowMapFilename);
	};
}

#endif
