#include "PositionUtils.h"
#include <math.h>
#include <cmath>
using namespace Utils;

#define NORMALIZE_ANGLE(angle)		\
{					\
if (angle < 0)				\
	angle += (2 * M_PI);		\
else if (angle >= (2 * M_PI))		\
	while (angle > (2 * M_PI))	\
		angle -= (2 * M_PI);	\
}					\


float PositionUtils::CalcDistance(Cell& from, Cell& to)
	{
		float dY = (signed)(to.getY() - from.getY());
		float dX = (signed)(to.getX() - from.getX());

		return sqrt(dX * dX + dY * dY);
	}

	float PositionUtils::CalcGradient(Cell& from, Cell& to)
	{
		float dY = (signed)(to.getY() - from.getY());
		float dX = (signed)(to.getX() - from.getX());

		if (to.getX() == from.getX())
			return FLT_MAX;
		else
			return fabs(dY/dX);
	}

	float PositionUtils::CalcLeftAngleCost(float from, float to)
	{
		float fLeftCost = (2 * M_PI) - (from - to);
		// return ((2 * M_PI) - CalcRightAngleCost(from, to));

		NORMALIZE_ANGLE(fLeftCost);

		return fLeftCost;
	}

	float PositionUtils::CalcRightAngleCost(float from, float to)
	{
		float fRightCost = (from - to);

		NORMALIZE_ANGLE(fRightCost);

		return fRightCost;
	}

	float PositionUtils::CalcGradientAngleOffset(Cell& from, Cell& to, float angle)
	{
		//float fGradient = SPosition::CalcGradient(from, to);
		float dY = (signed)(to.getY() - from.getY()) * (-1);
		float dX = (signed)(to.getX() - from.getX());

		float fNecessaryAngle = atan2(dY, dX);

		// tan counts from -90 degrees by our map bearing with the wrong sign
		float fMapBearing = ((fNecessaryAngle < 0) ? (2 * M_PI + fNecessaryAngle) : (fNecessaryAngle));// - (M_PI / 2);
		NORMALIZE_ANGLE(fMapBearing);

//		printf("Bearing %f needs to be fixed to %f\n", angle, fMapBearing);

		float fLeftCost = CalcLeftAngleCost(angle, fMapBearing);
		float fRightCost = CalcRightAngleCost(angle, fMapBearing);

		//printf("From bearing %f to %f (nec %f) you have: Right cost: %f, left cost: %f\n", angle, fMapBearing, fNecessaryAngle, fRightCost, fLeftCost);
		float fAngleOffset;

		// If turning right costs less, return it as a negative number
		if (fRightCost < fLeftCost)
			fAngleOffset = (-1 * fRightCost);
		// Otherwise it's to the left which is just a positive number
		else
			fAngleOffset =  (fLeftCost);

		//printf("Gradient from (%u, %u) to (%u, %u) is %f rads with tested %f, off by %f!\n",
		//from.dwX, from.dwY, to.dwX, to.dwY, fNecessaryAngle, angle, fAngleOffset);

		return fAngleOffset;
	}
