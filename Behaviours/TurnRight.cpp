#include "TurnRight.h"

TurnRight::TurnRight(Robot* robot):Behavior(robot)
{
}

bool TurnRight::startCond()
{
	for (int i = Helper::DegreesToIndex(0); i< Helper::DegreesToIndex(30); i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			for (int j = Helper::DegreesToIndex(-30); j < Helper::DegreesToIndex(0); j++)
			{
				if (_robot->getLaserDistance(j) > (Helper::MINIMUM_WALL_RANGE * 1.5))
				{
					cout << "TurnRight start cond triggered" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool TurnRight::stopCond()
{
	for (int i= Helper::DegreesToIndex(-30) ; i<(Helper::DegreesToIndex(30)) ; i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			cout << "TurnRight stop cond triggered" << endl;
			return true;
		}

	}
	return false;
}

void TurnRight::action()
{
	_robot->setSpeed(0.0,-1.5);
}

TurnRight::~TurnRight()
{
}
