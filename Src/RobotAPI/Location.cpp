#include "Location.h"

	Location::Location()
	{
		setX(0);
		setY(0);
		setYaw(0);
	}

	Location::Location(double x, double y, double yaw)
	{
		setX(x);
		setY(y);
		setYaw(yaw);
	}

	double Location::getX()
	{
		return _x;
	}

	double Location::getY()
	{
		return _y;
	}

	double Location::getYaw()
	{
		return _yaw;
	}

	void Location::setX(double x)
	{
		_x = x;
	}

	void Location::setY(double y)
	{
		_y = y;
	}

	void Location::setYaw(double yaw)
	{
		_yaw = yaw;
	}

	Location::~Location()
	{
	}
