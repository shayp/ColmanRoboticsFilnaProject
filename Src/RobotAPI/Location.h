#ifndef LOCATION_H_
#define LOCATION_H_

class Location
{
private:
	double _x;
	double _y;
	double _yaw;

public:
	Location();
	Location(double x, double y, double yaw);
	double getX();
	double getY();
	double getYaw();
	void setX(double x);
	void setY(double y);
	void setYaw(double yaw);
	~Location();
};

#endif /* LOCATION_H_ */
