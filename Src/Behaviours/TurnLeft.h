#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include <iostream>
#include "Behavior.h"
#include "GoForward.h"
#include "../RobotAPI/Robot.h"

class TurnLeft: public Behavior
{
public:
	TurnLeft(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~TurnLeft();
	static const float TURN_SPEED = 0.5;
};

#endif /* TurnLeft_H_ */
