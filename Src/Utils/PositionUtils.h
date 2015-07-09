#ifndef POSITION_UTILS_H
#define POSITION_UTILS_H
#include "../CoreLib/Cell.h"

using namespace std;
using namespace CoreLib;

namespace Utils
{

	class PositionUtils
	{
	public:
		static float CalcDistance(Cell& from, Cell& to);
		static float CalcGradient(Cell& from, Cell& to);
		static float CalcLeftAngleCost(float from, float to);
		static float CalcRightAngleCost(float from, float to);
		static float CalcGradientAngleOffset(Cell& from, Cell& to, float angle);
	};
}

#endif
