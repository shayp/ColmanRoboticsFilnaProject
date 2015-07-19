#include "TurnInPlace.h"
#include "../RobotAPI/Helper.h"

TurnInPlace::TurnInPlace(Robot* robot):Behavior(robot)
{
}

bool TurnInPlace::startCond()
{
	std::cout << "TurnInPlace start cond triggered" << std::endl;
	return true;
}

bool TurnInPlace::stopCond()
{

	for (int i= Helper::DegreesToIndex(-60) ; i<(Helper::DegreesToIndex(60)) ; i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			cout << "TurnInPlace stop cond triggered" << endl;
			return false;
		}

	}
	_robot->setSpeed(0.0,0.0);

	return true;

}

void TurnInPlace::action()
{
	_robot->setSpeed(0.0,0.2);
}

TurnInPlace::~TurnInPlace()
{
}
