#include "TurnLeft.h"

TurnLeft::TurnLeft(Robot* robot):Behavior(robot)
{
}

bool TurnLeft::startCond()
{
	for (int i = Helper::DegreesToIndex(-30); i< Helper::DegreesToIndex(0); i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			for (int j = Helper::DegreesToIndex(0); j < Helper::DegreesToIndex(30); j++)
			{
				if (_robot->getLaserDistance(j) > (Helper::MINIMUM_WALL_RANGE * 1.5))
				{
					cout << "TurnLeft start cond triggered" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool TurnLeft::stopCond()
{
	for (int i= Helper::DegreesToIndex(-30) ; i<(Helper::DegreesToIndex(30)) ; i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			cout << "TurnLeft stop cond triggered" << endl;
			return true;
		}

	}
	return false;
}

void TurnLeft::action()
{
	_robot->setSpeed(0.0,0.2);
}

TurnLeft::~TurnLeft()
{
}
