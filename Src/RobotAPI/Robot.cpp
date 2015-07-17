#include "Robot.h"
#include "../Utils/PositionUtils.h"

using namespace Utils;
Robot::Robot(char* ip, int port)
{
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);
	_location  = new Location(0,0,0);
	_pp->SetOdometry(0,0,0);
	while (_pp->GetXPos() != 0 || _pp->GetYPos() != 0 ||_pp->GetYPos() != 0)
	{
		_pp->SetOdometry(0,0,0);
	}

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

	//_location->setX(dX+ _location->getX());
	//_location->setY(dY+ _location->getY());

	PositionUtils::FixRad(dYaw);
}
void Robot::UpdateLocation(double x, double y, double yaw)//, bool isSetOdo)
{
	/*if (isSetOdo)
	{
		while (_pp->GetXPos() != x || _pp->GetYPos() != y ||_pp->GetYPos() != yaw)
		{
			_pp->SetOdometry(x,y,yaw);
		}
	}*/
	//_pp->SetOdometry(x,y,yaw);
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
