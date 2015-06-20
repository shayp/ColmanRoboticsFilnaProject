#include "PngUtils.h"
#include "../../Libs/PngLoader/lodepng.h"

#include <iostream>

#define R_OFFSET 0
#define G_OFFSET 1
#define B_OFFSET 2
#define A_OFFSET 3

using namespace std;
using namespace Utils;

unsigned char PngUtils::getPixelColor(const vector<unsigned char>& rawImage, unsigned width,
									  unsigned height, unsigned row, unsigned col)
{
	unsigned basePos = row * width * 4 + col * 4;

	if (width <= 0 || height <= 0 || basePos + A_OFFSET > rawImage.size())
	{
		return COLOR_INVALID;
	}

	if (rawImage[basePos + R_OFFSET] == COLOR_BLACK &&
		rawImage[basePos + G_OFFSET] == COLOR_BLACK  &&
		rawImage[basePos + B_OFFSET] == COLOR_BLACK)
	{
		return COLOR_BLACK;
	}

	return COLOR_WHITE;
}

void PngUtils::blowMap(string mapFilename, int numPixelsToBlow, string blowMapFilename)
{
	vector<unsigned char> image;
	unsigned width, height;
	unsigned x, y;

	unsigned decodeError = lodepng::decode(image, width, height, mapFilename);

	if (decodeError)
	{
		cout << "decoder error number " << decodeError << ": " << lodepng_error_text(decodeError) << endl;
	}

	vector<unsigned char> blowImage;
	blowImage.resize(width * height * 4);

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			unsigned basePos = y * width * 4 + x * 4;

			if (getPixelColor(image, width, height, y, x) == COLOR_BLACK)
			{
				for (int i = -numPixelsToBlow; i < numPixelsToBlow; i++)
				{
					for (int j = -numPixelsToBlow; j < numPixelsToBlow; j++)
					{
						int offset = 4 * i + (4 * width) * j;
						if (basePos + offset >= 0 && basePos + offset + B_OFFSET < image.size())
						{
							blowImage[basePos + offset + R_OFFSET] = COLOR_BLACK;
							blowImage[basePos + offset + G_OFFSET] = COLOR_BLACK;
							blowImage[basePos + offset + B_OFFSET] = COLOR_BLACK;
						}
					}
				}
			}
			else
			{
				blowImage[basePos + R_OFFSET] = COLOR_WHITE;
				blowImage[basePos + G_OFFSET] = COLOR_WHITE;
				blowImage[basePos + B_OFFSET] = COLOR_WHITE;
			}

			blowImage[basePos + A_OFFSET] = COLOR_WHITE;
		}
	}

	unsigned encodeError = lodepng::encode(blowMapFilename, blowImage, width, height);
	if (encodeError)
	{
		cout << "decoder error " << encodeError << ": " << lodepng_error_text(encodeError) << endl;
	}
}
