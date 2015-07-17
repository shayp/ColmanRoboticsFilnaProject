/*
 * FindDirection.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "FindDirection.h"
#include "../CoreLib/Cell.h"
using namespace CoreLib;
using namespace Utils;
FindDirection::FindDirection(Robot* robot) : Behavior(robot)
{
	_from = new Location();
	_from->setX(0);
	_from->setY(0);
	_from->setYaw(0);
	_to = new Location();
	_to->setX(40);
	_to->setY(40);
	//Get the delta in Rad and convert it to deg
	this->_degToWaypoint = (PositionUtils::CalcGradientAngleOffset(*_from,*_to,_robot->_location->getYaw()))*180/M_PI;;
}

bool FindDirection::startCond()
{
	cout << "FindDirection start condition started" << endl;
	return true;
}

void FindDirection::action()
{
	_robot->setSpeed(0.0, 0.0);
}

bool FindDirection::stopCond()
{

	if (this->_degToWaypoint<1 || this->_degToWaypoint>359)
	{
		cout << "FindDirection stop condition started" << endl;
		_robot->setSpeed(0.0, 0.0);
		return true;
	}

	//TODO:Check if this problem happened in the real robot
	//Fix Bug
	if(this->_degToWaypoint!=315)
	{
		//Update the spin speed
		this->_degToWaypoint = (PositionUtils::CalcGradientAngleOffset(*_from,*_to,_robot->_location->getYaw()))*180/M_PI;;
		this->_robot->setSpeed(0,PositionUtils::SpinSpeedByDeg(this->_degToWaypoint));
	}
	return false;
}

FindDirection::~FindDirection() {
	// TODO Auto-generated destructor stub
}

