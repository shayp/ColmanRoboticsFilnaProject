#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "Location.h"

using namespace PlayerCc;

class Robot
{
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Location* _location;
	Robot(char* ip, int port);
	void read();
	void setSpeed(float speed, float angularSpeed);
	void getDelta(double &dX,double &dY,double &dYaw);
	float getLaserDistance(int index);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
