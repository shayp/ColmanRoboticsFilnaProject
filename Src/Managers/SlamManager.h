/*
 * SlamManager.h
 *
 */

#ifndef SLAMMANAGER_H_
#define SLAMMANAGER_H_

#include "../CoreLib/Particle.h"
#include <vector>

#define PART_COUNT 20
#define THRESH_LOW 0.5
#define THRESH_HIGH 0.8
#define RADIUS 6
using namespace CoreLib;

typedef vector <Particle> particlesVec;

//Class which controls all aspects following the slam system control
class SlamManager {
public:

	particlesVec particles; //Vector which hold all particles

	//Constructor of objects type of SlamManager
	SlamManager(float xRobot,float yRobot,float yawRobot);

	//Method that initiates all the particles
	void InitParticles(float xRobot,float yRobot,float yawRobot);

	//Method that updates all the particles in the vector
	void UpdateParticles(float delX, float delY, float delTetha,float laserScan[], int laserCount);

	//Method that returns the location of the robot by the slam system.
	void GetLocationByParticles(float &x,float &y,float &yaw);

	//Destructor of objects type of SlamManager
	virtual ~SlamManager();
};

#endif /* SLAMALGO_H_ */
