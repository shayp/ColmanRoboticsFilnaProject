/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: user
 */

#include "PlnObstacleAvoid.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot):Plan(robot)
{
	//Creating behaviors
	_behArr = new Behavior*[6];
	_behArr[0] = new TurnInPlace(_robot);
	_behArr[1] = new FindDirection(_robot);
	_behArr[2] = new ForwardToWayPoint(_robot);
	_behArr[3] = new AvoidTurnInPlace(_robot);
	_behArr[4] = new AvoidForward(_robot);
	_behArr[5] = new AvoidSwitchDirection(_robot);


	//Build  plan

	//TurnInPlace
	_behArr[0]->addNext(_behArr[1]);


	//FindDirection
	_behArr[1]->addNext(_behArr[2]);

	//ForwardToWayPoint
	_behArr[2]->addNext(_behArr[3]);

	//AvoidTurnInPlace
	_behArr[3]->addNext(_behArr[4]);

	//AvoidForward
	_behArr[4]->addNext(_behArr[1]);
	_behArr[4]->addNext(_behArr[5]);

	//AvoidSwitchDirection
	_behArr[5]->addNext(_behArr[4]);

	//Start at
	_starBeh = _behArr[0];
}

Behavior* PlnObstacleAvoid::startPoint()
{
	return _starBeh;
}

PlnObstacleAvoid::~PlnObstacleAvoid()
{
	delete _behArr[0];
	delete _behArr[1];
	delete _behArr[2];
	delete _behArr[3];
	delete _behArr[4];

	delete[] _behArr;
}

