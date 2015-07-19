#ifndef HELPER_H_
#define HELPER_H_

#define SCAN_SPAN  666
#define DEGREES 270
#define PI 3.1415926536

#include <math.h>
#include <iostream>

class Helper
{

public:
	static constexpr float MINIMUM_WALL_RANGE_SIDES = 0.6;
	static constexpr float MINIMUM_WALL_RANGE_FORWARD = 1;
	static constexpr float MINIMUM_WALL_RANGE = 0.5;
	static constexpr float TOTAL_SCAN_SPAN = SCAN_SPAN;
	static constexpr float HALF_SCAN_SPAN = SCAN_SPAN / 2;
	static constexpr float TOTAL_DEGREES = DEGREES;

	static constexpr float DEGREES_INDEX_RATIO = SCAN_SPAN / DEGREES;

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

	//Calc the angl between the from to to
	static double CalcRadToWaypointWithoutYaw(double fromX, double fromY, double toX, double toY);

	//Calc the angle we need to pass for been in straight line to the to point
	static double CalcRadDeltaToWaypoint(double fromX, double fromY, double toX, double toY, double fromYaw);

	static double KeepYawInRange(double rad);
	static double SpinSpeedByDeg(double rad);


	static double ConvertTo2PI(double rad);

};

#endif /* HELPER_H_ */
