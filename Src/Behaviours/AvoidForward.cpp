/*
 * AvoidForward.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "AvoidForward.h"

AvoidForward::AvoidForward(Robot* robot) : Behavior(robot)
{
	// TODO Auto-generated constructor stub

}


bool AvoidForward::startCond()
{

	cout << "AvoidForward start condition started" << endl;
	double deltaToWaypoint = Helper::CalcRadDeltaToWaypoint(this->_robot->_location->getX(),this->_robot->_location->getY(),this->_robot->waypointX, this->_robot->waypointY, this->_robot->_location->getYaw());

	//The waypoint is to my right
	if(deltaToWaypoint>0)
	{
		this->_turnleft = true;
	}
	//The waypoint is to my left
	else
	{
		this->_turnleft = false;
	}




	return true;
}

bool AvoidForward::stopCond()
{
	//Is there obstacle in front
	for (int i= Helper::DegreesToIndex(-60) ; i < Helper::DegreesToIndex(60) ; i++)
	{
		//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			cout << "AvoidForward stop condition started because to close to wall" << endl;
			_robot->setSpeed(0.0, 0.0);
			return true;
		}
	}

	if(this->_turnleft)
	{
		//Is there place to turn right
		for (int i= Helper::DegreesToIndex(-60) ; i < Helper::DegreesToIndex(135) ; i++)
		{
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (_robot->getLaserDistance(i) < 1.5*Helper::MINIMUM_WALL_RANGE)
			{
				return false;
			}
		}
	}

	else
	{
		//Is there place to turn left
		for (int i= Helper::DegreesToIndex(-135) ; i < Helper::DegreesToIndex(60) ; i++)
		{
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (_robot->getLaserDistance(i) < 1.5*Helper::MINIMUM_WALL_RANGE)
			{
				_robot->setSpeed(0.0, 0.0);
				return false;
			}
		}
	}
	//Nothing stop me from return going to waypoint
	_robot->setSpeed(0.0, 0.0);
	cout << "AvoidForward stop condition started because can keep in the waypoint direction"<< endl;
	return true;
}


void AvoidForward::action()
{
	_robot->setSpeed(0.12, 0.0);
}

AvoidForward::~AvoidForward() {
	// TODO Auto-generated destructor stub
}

