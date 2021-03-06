#ifndef MANAGER_H_
#define MANAGER_H_

#include "../Plans/Plan.h"
#include "../Behaviours/Behavior.h"
#include "../RobotAPI/Robot.h"
#include "../Utils/PositionUtils.h"
#include "SlamManager.h"

class Manager
{
private:
	Robot* _robot;
	Plan* _plan;
	Behavior* _curr;
	SlamManager* _slamManager;
	float _laserScan[SCAN_SPAN];
	int countSlamExe;
	double dX, dY, dYaw;


public:

	Manager(Robot* robot, Plan* plan);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
