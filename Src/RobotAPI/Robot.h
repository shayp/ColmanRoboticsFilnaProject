#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "Location.h"
#include "../Utils/PositionUtils.h"
#include "../RobotAPI/Helper.h"
using namespace PlayerCc;

class Robot
{
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Location* _location;
	double waypointX, waypointY;
	Robot(char* ip, int port);
	void read();
	void setSpeed(float speed, float angularSpeed);
	void getDelta(double &dX,double &dY,double &dYaw);
	void UpdateLocation(double x, double y, double yaw);
	LaserProxy* GetLaserProxy() {
		return _lp;
	}
	float getLaserDistance(int index);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
