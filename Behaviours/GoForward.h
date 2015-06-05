#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include <iostream>
#include "Behavior.h"
#include "../Robot.h"

class GoForward: public Behavior
{
public:
	GoForward(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~GoForward();
};

#endif /* GOFORWARD_H_ */
