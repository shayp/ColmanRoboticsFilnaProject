#ifndef HELPER_H_
#define HELPER_H_

#define SCAN_SPAN  666
#define DEGREES 270
#define PI 3.1415926536

class Helper
{

public:
	static const float MINIMUM_WALL_RANGE_SIDES = 0.6;
	static const float MINIMUM_WALL_RANGE_FORWARD = 1;
	static const float MINIMUM_WALL_RANGE = 0.8;
	static const float TOTAL_SCAN_SPAN = SCAN_SPAN;
	static const float HALF_SCAN_SPAN = SCAN_SPAN / 2;
	static const float TOTAL_DEGREES = DEGREES;

	static const float DEGREES_INDEX_RATIO = SCAN_SPAN / DEGREES;

	static const int FREE_CELL = 0;
	static const int OCCUPIED_CELL = 1;
	static const int UNKNOWN_CELL = 2;

	static const int MAP_ROWS = 100;
	static const int MAP_COLUMNS = 100;
	static const int MAP_RESOLUTION = 5;

	static int IndexToDegrees(int index);
	static int DegreesToIndex(int degrees);

	static double IndexToRadians(int index);
	static int RadiansToIndex(double radians);

	static double MetersToCentimeters(double meters);
	static double CentimetersToMeters(double centimeters);

};

#endif /* HELPER_H_ */
