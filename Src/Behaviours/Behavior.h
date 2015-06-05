#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../RobotAPI/Robot.h"
#include "../RobotAPI/Helper.h"

using namespace std;

class Behavior
{
	Behavior** _next;
	int _arrSize;
protected:
	Robot* _robot;
public:
	Behavior(Robot* robot);
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	Behavior* addNext(Behavior* beh);
	Behavior* selectNext();
	virtual ~Behavior();
};

#endif /* BEHAVIOR_H_ */
