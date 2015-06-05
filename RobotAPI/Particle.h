#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Map.h"
#include "Location.h"

#define MAX_ACCURATE_ANGLE_TO_MOVE 1.0
#define NORMAL_ACCURATE_ANGLE_TO_MOVE 0.5
#define SAFE_DISTANCE_TO_MOVE 0.3
#define LASER_MAX_RANGE 4
#define LASER_ANGLE_RANGE 240
#define OPEN_PATH_RANGE 0.75
#define ROBOT_DIMENTION_ON_MAP 2
#define SENSOR_FROM_END 15
#define SENSOR_DETECTION_RANGE 60
#define PARTICLE_CLOUD_RADIUS 15.0

class Particle
{

private:
	Location _location;
	Map _map;
	double _belief;
    void updateCellRangeToFree(int laserIndex, double range, int &countHit, int &countMiss);
    void updateCellToOccupied(float laserScan[], int i, int &countHit, int &countMiss);

public:
	Particle(double x, double y);
	void updateParticle(double deltaX, double deltaY, double deltaYaw, float laserScan[]);
	double calculatePrediction(double deltaX, double deltaY, double deltaYaw);
	double probabilityUpdateMapUsingScan(float laserScan[]);
	void setMap(Map map);
	Map getMap();
	double getBelief();
	void printMap();
	void setYaw(double yaw);
	Location* getLocation();
	~Particle();
};

#endif /* PARTICLE_H_ */
