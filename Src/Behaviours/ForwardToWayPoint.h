/*
 * ForwardToWayPoint.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef FORWARDTOWAYPOINT_H_
#define FORWARDTOWAYPOINT_H_

#include <iostream>
#include "Behavior.h"
#include "../RobotAPI/Robot.h"
#include <math.h>

class ForwardToWayPoint: public Behavior
{
public:
	ForwardToWayPoint(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~ForwardToWayPoint();
};

#endif /* FORWARDTOWAYPOINT_H_ */

