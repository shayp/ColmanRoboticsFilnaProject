/*
 * ForwardToWayPoint.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */
#if 0
#ifndef FORWARDTOWAYPOINT_H_
#define FORWARDTOWAYPOINT_H_

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

#endif
