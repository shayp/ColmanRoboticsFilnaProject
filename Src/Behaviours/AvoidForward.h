/*
 * AvoidForward.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef AVOIDFORWARD_H_
#define AVOIDFORWARD_H_

#include <iostream>
#include "Behavior.h"
#include "../RobotAPI/Robot.h"

class AvoidForward: public Behavior
{
	bool _turnleft;
public:
	AvoidForward(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~AvoidForward();
};

#endif /* AVOIDFORWARD_H_ */
