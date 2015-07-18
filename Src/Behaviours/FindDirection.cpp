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

	//TODO:Change to work with Location instead _pp



	//Get the delta in Rad and convert it to deg
	//this->_degToWaypoint = (PositionUtils::CalcGradientAngleOffset(*_from,*_to,_robot->_location->getYaw()))*180/M_PI;;
}

bool FindDirection::startCond()
{

	cout << "FindDirection start condition started" << endl;
	double temp = Helper::CalcRadToWaypointWithoutYaw(this->_robot->_location->getX(),this->_robot->_location->getY(),this->_robot->waypointX,this->_robot->waypointY);
	this->_degToWaypoint = Helper::CalcRadDeltaToWaypoint(this->_robot->_location->getYaw(),temp);
	this->_degToWaypoint= this->_degToWaypoint*180/M_PI;

	return true;
}

void FindDirection::action()
{
	double radToDestPoint = Helper::CalcRadToWaypointWithoutYaw(this->_robot->_location->getX(),this->_robot->_location->getY(),this->_robot->waypointX,this->_robot->waypointY);

	double deltaYaw = Helper::CalcRadDeltaToWaypoint(this->_robot->_location->getYaw(),radToDestPoint);


	//Fix Bug
		//float robotDegreeTemp = (PositionUtils::CalcGradientAngleOffset(*_from,*_to,_robot->_location->getYaw()))*180/M_PI;
		//if (robotDegreeTemp > -44.0 || robotDegreeTemp < -46.0)
			this->_degToWaypoint = deltaYaw*180/M_PI;
		cout <<"deg: " << this->_degToWaypoint << endl;
		//if(this->_degToWaypoint>-44.0 || this->_degToWaypoint<-46.0)
		//{
			//Update the spin speed
		cout << "the DELTA: " << deltaYaw << endl;
		this->_robot->setSpeed(0,Helper::SpinSpeedByDeg(deltaYaw));
//}
}

bool FindDirection::stopCond()
{

	if ((this->_degToWaypoint>0 && this->_degToWaypoint<1) || (this->_degToWaypoint>359 && this->_degToWaypoint<360))
	{
		cout << "FindDirection stop condition started" << endl;
		_robot->setSpeed(0.0, 0.0);
		return true;
	}

	//TODO:Check if this problem happened in the real robot
	cout << "DIDNT STOP BECAUSE THE SIZE IS: " << this->_degToWaypoint << endl;
	return false;
}

FindDirection::~FindDirection() {
	// TODO Auto-generated destructor stub
}
