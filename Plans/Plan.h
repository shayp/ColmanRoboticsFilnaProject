#ifndef PLAN_H_
#define PLAN_H_

#include "../Behaviours/Behavior.h"

class Plan
{
protected:
	Behavior** _behArr;
	Robot* _robot;
	Behavior* _starBeh;
public:
	Plan(Robot* robot);
	virtual Behavior* startPoint()=0;
	virtual ~Plan();
};

#endif /* PLAN_H_ */
