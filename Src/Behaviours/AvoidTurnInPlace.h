/*
 * AvoidTurnInPlace.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef AVOIDTURNINPLACE_H_
#define AVOIDTURNINPLACE_H_

#include <iostream>
#include "Behavior.h"
#include "../RobotAPI/Robot.h"

class AvoidTurnInPlace : public Behavior
{
	int _turnDirection;
public:
	AvoidTurnInPlace(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~AvoidTurnInPlace();
};

#endif /* AVOIDTURNINPLACE_H_ */
