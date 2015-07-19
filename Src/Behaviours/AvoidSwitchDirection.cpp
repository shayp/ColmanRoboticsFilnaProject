/*
 * AvoidSwitchDirection.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#include "AvoidSwitchDirection.h"

AvoidSwitchDirection::AvoidSwitchDirection(Robot* robot) : Behavior(robot)
{


}

	bool AvoidSwitchDirection::startCond()
	{
		//Is there obstacle in front
		for (int i= Helper::DegreesToIndex(-60) ; i < Helper::DegreesToIndex(60) ; i++)
		{
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
			{
				cout << "AvoidSwitchDirection start condition started" << endl;

				//Find the spin direction
				double deltaToWaypoint = Helper::CalcRadDeltaToWaypoint(this->_robot->_location->getX(),this->_robot->_location->getY(),this->_robot->waypointX, this->_robot->waypointY, this->_robot->_location->getYaw());


				//The waypoint is to my right
				if(deltaToWaypoint>0)
				{
					this->_turnDirection = 1;
				}
				//The waypoint is to my left
				else
				{
					this->_turnDirection = -1;
				}


				return true;
			}
		}

		return false;

	}

	bool AvoidSwitchDirection::stopCond()
	{
		for (int i= Helper::DegreesToIndex(-15) ; i < Helper::DegreesToIndex(15) ; i++)
		{
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (this->_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE*1.5)
			{
				return false;
			}
		}
		cout << "AvoidSwitchDirection stop  condition started" << endl;
		return true;
	}

	void AvoidSwitchDirection::action()
	{
		//If better turn left the spin direction is negative=left and if not its positive=right
		_robot->setSpeed(0,this->_turnDirection*0.2);
	}

AvoidSwitchDirection::~AvoidSwitchDirection() {
	// TODO Auto-generated destructor stub
}

