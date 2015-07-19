/*
 * ForwardToWayPoint.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "ForwardToWayPoint.h"
#include "../Managers/SimManager.h"
int 	ForwardToWayPoint::WayPointIndex = 1;

ForwardToWayPoint::ForwardToWayPoint(Robot* robot) : Behavior(robot)
{
	// TODO Auto-generated constructor stub
	this->_robot->waypointX = SimManager::GetInstance()->GetAllWayPoints()[1]->getX();
	this->_robot->waypointY = SimManager::GetInstance()->GetAllWayPoints()[1]->getY();

}
bool ForwardToWayPoint::startCond()
{
	if(abs((this->_robot->waypointX - this->_robot->_location->getX())) + abs((this->_robot->waypointY - this->_robot->_location->getY())) < 0.2)
		return false;

	cout << "ForwardToWayPoint start cond triggered" << endl;
	return true;
}
bool ForwardToWayPoint::stopCond()
{

	double XDistance = (this->_robot->waypointX - this->_robot->_location->getX());
	double YDistance = (this->_robot->waypointY - this->_robot->_location->getY());
	XDistance *= XDistance;
	YDistance *= YDistance;
	cout << "WayPointX = " << this->_robot->waypointX << " Location X=" << this->_robot->_location->getX()
			<< "WayPointY = " << this->_robot->waypointY << " Location Y=" << this->_robot->_location->getY()
			<< " The distance: " << sqrt(XDistance + YDistance) << endl;
	if(sqrt(XDistance + YDistance) < 0.1)
	{

		ForwardToWayPoint::WayPointIndex++;
		if (ForwardToWayPoint::WayPointIndex > SimManager::GetInstance()->GetAllWayPoints().size())
		{
			cout << "We Got to the last way point BYE BYE Mrs american pie" << endl;
			exit(1);
		}
		cout << "waypoint x: "<< this->_robot->waypointX << " real X: " <<this->_robot->_location->getX() << endl;
		cout << "@#$%@#$%#@%#%@@#@%#ForwardToWayPoint stop cond triggered because too close" << endl;
		this->_robot->waypointX = SimManager::GetInstance()->GetAllWayPoints()[ForwardToWayPoint::WayPointIndex]->getX();
		this->_robot->waypointY = SimManager::GetInstance()->GetAllWayPoints()[ForwardToWayPoint::WayPointIndex]->getY();

		_robot->setSpeed(0, 0);
		return true;
	}
	else
	{
		for (int i= Helper::DegreesToIndex(-30) ; i < Helper::DegreesToIndex(30) ; i++)
		{
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (_robot->getLaserDistance(i) < 0.3)
			{
				cout << "ForwardToWayPoint stop cond triggered" << endl;
				return true;
			}
		}
	}
		return false;
}


void ForwardToWayPoint::action()
{
	cout << "ForwardToWayPoint action started" << endl;
	_robot->setSpeed(0.12, 0.0);

}

ForwardToWayPoint::~ForwardToWayPoint() {
	// TODO Auto-generated destructor stub
}
