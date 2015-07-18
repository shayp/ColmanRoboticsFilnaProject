#include "Manager.h"
using namespace Utils;

Manager::Manager(Robot* robot, Plan* plan)
{
	_robot = robot;
	_plan = plan;
	_curr = plan->startPoint();
	_slamManager = new SlamManager(_robot->_location->getX(),
		_robot->_location->getY(), _robot ->_location->getYaw());
    countSlamExe = 0;
	dX = 0;
	dY = 0;
	dYaw = 0;
}

void Manager::run()
{
	double x,y,yaw,dX,dY,dYaw;
	int i;
	_robot->getDelta(dX,dY,dYaw);

	_robot->read();

	if (_curr->startCond() == false)
	{
		return;
	}

	_curr->action();
	float laserMaxRange;
	while(true)
	{
		_robot->read();
		//_slamManager->UpdateParticles(dX, dY, dYaw, _laserScan, SCAN_SPAN);

		// TODO: Check where to place and uncomment
		//_slamManager->PrintParticles();

		while ((_curr->stopCond()) == false)
		{
			// Notice: i moved the nexr  2 line of actio and read above the slam
			_curr->action();
			_robot->read();


			_robot->getDelta(dX,dY,dYaw);
			 for (i = 0; i < SCAN_SPAN; i++)
				 _laserScan[i] = _robot->getLaserDistance(i);

				// TODO: Check where to place and uncomment
			//_slamManager->UpdateParticles(dX, dY, dYaw, _laserScan, SCAN_SPAN,_robot->GetLaserProxy());
			//_slamManager->GetLocationByParticles(x,y,yaw);
			//_robot->UpdateLocation(x,y,yaw);

			_robot->getDelta(dX,dY,dYaw);

		// _slamManager->UpdateParticles(dX, dY, dYaw, _laserScan);

		}

		this->_curr = _curr->selectNext();
		 if(!_curr)
		 {
			 break;
		 }
		 for (int i = 0; i < SCAN_SPAN; i++)
		 _laserScan[i] = _robot->getLaserDistance(i);
	}
}

Manager::~Manager() {
}
