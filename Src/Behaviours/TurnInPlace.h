#ifndef TURNINPLACE_H_
#define TURNINPLACE_H_

#include <iostream>
#include "Behavior.h"
#include "GoForward.h"
#include "../RobotAPI/Robot.h"

class TurnInPlace: public Behavior
{
public:
	TurnInPlace(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~TurnInPlace();
};

#endif /* TURNINPLACE_H_ */
