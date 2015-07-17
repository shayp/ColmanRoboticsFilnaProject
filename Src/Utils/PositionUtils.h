#ifndef POSITION_UTILS_H
#define POSITION_UTILS_H
#include "../RobotAPI/Location.h"

using namespace std;

#define NORMALIZE_ANGLE(angle)		\
{					\
if (angle < 0)				\
	angle += (2 * M_PI);		\
else if (angle >= (2 * M_PI))		\
	while (angle > (2 * M_PI))	\
		angle -= (2 * M_PI);	\
}					\


namespace Utils
{


	class PositionUtils
	{
	public:
		static float CalcDistance(Location& from, Location& to);
		static float CalcGradient(Location& from, Location& to);
		static float CalcLeftAngleCost(float from, float to);
		static float CalcRightAngleCost(float from, float to);
		static float CalcGradientAngleOffset(Location& from, Location& to, float angle);
		static double SpinSpeedByDeg(float deg);
		static void FixRad(double &rad);
	};
}

#endif
