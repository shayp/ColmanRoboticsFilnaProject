#include "GoForward.h"

GoForward::GoForward(Robot* robot) : Behavior(robot)
{
}

bool GoForward::startCond()
{
	cout << "GoForward start cond triggered" << endl;
	return true;
}

void GoForward::action()
{
	_robot->setSpeed(1, 0.0);
}

bool GoForward::stopCond()
{

		for (int i= Helper::DegreesToIndex(-30) ; i < Helper::DegreesToIndex(30) ; i++)
		{
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
			{
				cout << "GoForward stop cond triggered" << endl;
				return true;
			}
		}
		return false;

}

GoForward::~GoForward()
{
}
