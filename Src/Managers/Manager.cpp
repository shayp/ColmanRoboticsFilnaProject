#include "Manager.h"

Manager::Manager(Robot* robot, Plan* plan) {
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
	_robot->read();

	//_slamManager->UpdateParticles(dX, dY, dYaw, _laserScan, SCAN_SPAN);
	//			_slamManager->PrintParticles();
	if (_curr->startCond() == false)
	{
		return;
	}

	_curr->action();

	while(true)
	{
		_robot->read();
		//_slamManager->UpdateParticles(dX, dY, dYaw, _laserScan, SCAN_SPAN);
		_slamManager->PrintParticles();
		while ((_curr->stopCond()) == false)
		{
			//cout << "while is true" << endl;
			//cout << dX << "  " << dY << "  " << dYaw << endl;
			_slamManager->UpdateParticles(dX, dY, dYaw, _laserScan, SCAN_SPAN);
			//cout << "update particle succeeded" << endl;
			_slamManager->PrintParticles();
			/*
			// update particles on every 10th action
			if (countSlamExe % 10 == 0)
			{
				_robot->getDelta(dX, dY, dYaw);

				for (int i = 0; i < Helper::TOTAL_SCAN_SPAN; i++)
				{
					_laserScan[i] = _robot->getLaserDistance(i);
				}

				_robot->setSpeed(0.0, 0.0);
				_slamManager->UpdateParticles(dX, dY, dYaw, _laserScan);
			}

			countSlamExe++;
		*/
			_curr->action();
			_robot->read();
			_robot->getDelta(dX,dY,dYaw);
		}
		//cout << "out of while!" << endl;
		_curr = _curr->selectNext();
		_curr->action();

		if(_curr->stopCond())
		 {
		 _curr = _curr->selectNext();
		 if(!_curr)
		 {
		 break;
		 }
		 }
		 _robot->getDelta(dX,dY,dYaw);
		 for (int i = 0; i < SCAN_SPAN; i++)
		 _laserScan[i] = _robot->getLaserDistance(i);
		// _slamManager->UpdateParticles(dX, dY, dYaw, _laserScan);

	}
}

Manager::~Manager() {
}
