#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "Plan.h"
#include "../Behaviours/GoForward.h"
#include "../Behaviours/TurnLeft.h"
#include "../Behaviours/TurnRight.h"
#include "../Behaviours/TurnInPlace.h"
#include "../Behaviours/FindDirection.h"

class PlnObstacleAvoid: public Plan
{
public:
	PlnObstacleAvoid(Robot* robot);
	 Behavior* startPoint();
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
