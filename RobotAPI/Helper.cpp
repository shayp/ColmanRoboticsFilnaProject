#include "Helper.h"

int Helper::DegreesToIndex(int degrees)
{
	int indexDifference = degrees * Helper::DEGREES_INDEX_RATIO;
	return Helper::HALF_SCAN_SPAN + indexDifference;
}

int Helper::IndexToDegrees(int index)
{
	int relativeIndex = index - Helper::HALF_SCAN_SPAN;
	return relativeIndex / Helper::DEGREES_INDEX_RATIO;
}

double Helper::IndexToRadians(int index)
{
	int degrees = IndexToDegrees(index);
	return degrees * PI / 180;
}

int Helper::RadiansToIndex(double radians)
{
	int degrees = radians * 180 / PI;
	return DegreesToIndex(degrees);
}

double Helper::MetersToCentimeters(double meters)
{
	return meters * 100;
}

double Helper::CentimetersToMeters(double centimeters)
{
	return centimeters / 100;
}

