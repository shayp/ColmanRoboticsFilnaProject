/*
 * AvoidSwitchDirection.h
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#ifndef AVOIDSWITCHDIRECTION_H_
#define AVOIDSWITCHDIRECTION_H_

#include <iostream>
#include "Behavior.h"
#include "../RobotAPI/Robot.h"

class AvoidSwitchDirection : public Behavior
{
	int _turnDirection;
public:
	AvoidSwitchDirection(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~AvoidSwitchDirection();
};

#endif /* AVOIDSWITCHDIRECTION_H_ */
