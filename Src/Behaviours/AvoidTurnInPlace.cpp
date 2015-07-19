/*
 * AvoidTurnInPlace.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "AvoidTurnInPlace.h"

AvoidTurnInPlace::AvoidTurnInPlace(Robot* robot) : Behavior(robot)
{
	//Defaulte turn right
	this->_turnDirection = 1;
}

	bool AvoidTurnInPlace::startCond()
	{
		cout << "AvoidTurnInPlace start condition started" << endl;
		int leftCounter = 0;
		int rightCounter = 0;

		for (int i= Helper::DegreesToIndex(-60) ; i < Helper::DegreesToIndex(0) ; i++)
		{
			leftCounter += this->_robot->getLaserDistance(i);
			/*
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
			{
				leftCounter++;
			}
			*/
		}

		for (int i= Helper::DegreesToIndex(0) ; i < Helper::DegreesToIndex(60) ; i++)
		{
			rightCounter += this->_robot->getLaserDistance(i);
			/*
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
			{
				rightCounter++;
			}
			*/
		}
		//Its better turn left
		if(leftCounter>rightCounter)
		{
			this->_turnDirection = -1;
		}
		return true;
	}


	bool AvoidTurnInPlace::stopCond()
	{
		for (int i= Helper::DegreesToIndex(-60) ; i < Helper::DegreesToIndex(60) ; i++)
		{
			//cout << "forward dist: "<< _robot->getLaserDistance(i) << " , " << i << endl;
			if (this->_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
			{
				return false;
			}
		}
		cout << "AvoidTurnInPlace stop  condition started" << endl;
		return true;
	}

	void AvoidTurnInPlace::action()
	{
		//If better turn left the spin direction is negative=left and if not its positive=right
		_robot->setSpeed(0,this->_turnDirection*0.2);
	}

AvoidTurnInPlace::~AvoidTurnInPlace() {
	// TODO Auto-generated destructor stub
}

