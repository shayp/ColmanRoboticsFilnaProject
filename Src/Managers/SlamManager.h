/*
 * SlamManager.h
 *
 */

#ifndef SLAMMANAGER_H_
#define SLAMMANAGER_H_

#include "../CoreLib/Particle.h"
#include <vector>

#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

#define PART_COUNT 50
#define THRESH_LOW 0.5
#define THRESH_HIGH 0.8
#define RADIUS 0.1
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
	void UpdateParticles(float delX, float delY, float delTetha,float laserScan[], int laserCount,LaserProxy* lp);

	//Method that returns the location of the robot by the slam system.
	bool GetLocationByParticles(double &x,double &y,double &yaw);

	//for debug
	void PrintParticles() {
		particlesVec::iterator pCurr = particles.begin();
		particlesVec::iterator pEnd = particles.end();
		int counter = 0;
		if (particles.size() == 0){
			cout << "0 PARTICLES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			exit(1);
		}
				for (; counter < particles.size(); pCurr++) {
					cout << "=============================================" << endl;
					cout << "Particle " << counter << " :" << endl;
					pCurr->PrintParticle();
					cout << "=============================================" << endl;
					counter++;
				}
			}

	//Destructor of objects type of SlamManager
	virtual ~SlamManager();
};

#endif /* SLAMALGO_H_ */
