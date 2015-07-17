#include "Robot.h"
#include "../Utils/PositionUtils.h"

using namespace Utils;
Robot::Robot(char* ip, int port)
{
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);
	_location  = new Location(0,0,0);

	_pp->SetMotorEnable(true);
	int i;

	//Fix the player bug
	for(i=0;i<15;i++)
		_pc->Read();
}

void Robot::read()
{
	_pc->Read();
}

void Robot::getDelta(double &dX,double &dY,double &dYaw)
{
	dX = _pp->GetXPos() - _location->getX();
	dY = _pp->GetYPos() - _location->getY();
	dYaw = _pp->GetYaw() - _location->getYaw();

	_location->setX(dX);
	_location->setY(dY);

	PositionUtils::FixRad(dYaw);

	_location->setYaw(dYaw);
}

void Robot::setSpeed(float speed, float angularSpeed)
{
	_pp->SetSpeed(speed,angularSpeed);
}

float Robot::getLaserDistance(int index)
{
	return _lp->GetRange(index);
}

Robot::~Robot()
{
	delete _lp;
	delete _pp;
	delete _pc;
}
