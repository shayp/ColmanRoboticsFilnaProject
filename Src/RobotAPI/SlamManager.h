#ifndef SLAMMANAGER_H_
#define SLAMMANAGER_H_

#include <vector>
#include <libplayerc++/playerc++.h>

#include "Particle.h"

#define PARTICLES_MAX_QUANTITY 100
#define BELIEF_THRESHOLD 0.6
typedef vector<Particle> ParticlesVector;

class SlamManager
{

private:
	ParticlesVector _particleVector;

public:
	SlamManager(double x,double y);
	void InitParticles(double x,double y);
	void UpdateParticles(double dX, double dY, double dYaw, float laserScan[]);
	virtual ~SlamManager();
};

#endif /* SLAMMANAGER_H_ */
