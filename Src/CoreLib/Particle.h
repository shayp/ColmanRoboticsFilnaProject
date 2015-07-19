/*
 * Particle.h
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Map.h"

#define MAX_ACCURATE_ANGLE_TO_MOVE 1.0
#define NORMAL_ACCURATE_ANGLE_TO_MOVE 0.5
#define SAFE_DISTANCE_TO_MOVE 0.3
#define NORMALIZEDFACTOR 1.1
#define LASER_MAX_RANGE 4.095
#define LASER_ANGLE_RANGE 240
#define OPEN_PATH_RANGE 0.75
#define RTOD(r)   ((r) * 180 / M_PI)
#define DTOR(d)   ((d) * M_PI / 180)
#define NORMALIZE(z)   atan2(sin(z), cos(z))
#define M_TO_CM(m)   (m * 100)
#define ROBOT_DIM 2
#define SENSOR_FROM_END 15
#define SENSOR_DETECTION_RANGE 60
#define CELL_DIM 5
#define INDEX_PER_DEGREE 6
#define MAX_DEGREE 360

#include <libplayerc++/playerc++.h>
#include "../RobotAPI/Helper.h"
using namespace PlayerCc;
using namespace std;

namespace CoreLib {
//Class which controls all aspects following the particle's system control
class Particle {
public:
	double pX;
	double pY;
	double pYaw;
	double pBelief;

	//Constructors of objects type of Particle
	Particle(float x, float y, float yaw, float belief);

	//Method which handles the particle position update
	void UpdateParticle(float delX, float delY, float delYaw, float* laserScan,
			int laserCount, LaserProxy* lp);

	//Method which calculate the particle's probability by map
	float ProbUpdateByScan(float laserScan[], int laserCount, LaserProxy* lp);

	void SetBelief(double bel) {
		if (bel > 1)
			pBelief = 1;
		else if (bel < 0)
			pBelief = 0;
		else
			pBelief = bel;
	}

	void SetYaw(double yaw) {
		pYaw = yaw;
		Helper::KeepYawInRange(pYaw);
	}

	double GetBelief();

	double GetX();

	double GetY();

	double GetYaw();

	//Method which converts laser index to angle
	float ConverteIndexToAngle(int index, int x, int radius);

	// Destructor of objects type of Particle
	~Particle();

	// for debugging.
	void PrintParticle() {
		cout << "x: " << pX << "      y: " << pY << "     yaw: " << pYaw
				<< "    " << "belief: " << pBelief << endl;
	}
};
}
#endif /* PARTICLE_H_ */
