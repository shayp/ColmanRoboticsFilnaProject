#include "SlamManager.h"

SlamManager::SlamManager(double x,double y)
{
	srand(time(NULL));
	InitParticles(x,y);
}

void SlamManager::InitParticles(double x,double y)
{
	for (int i = 0; i < PARTICLES_MAX_QUANTITY; i++)
	{
		Particle particle(x,y);
		_particleVector.push_back(particle);
	}
}

void SlamManager::UpdateParticles(double dX, double dY, double dYaw, float laserScan[])
{
	ParticlesVector::iterator particlesVectorBegining = _particleVector.begin();
	ParticlesVector::iterator particlesVectorEnding = _particleVector.end();

	int goodParticlesCounter = 0;

	while(particlesVectorBegining != particlesVectorEnding)
	{
		particlesVectorBegining->updateParticle(dX, dY, dYaw, laserScan);

		if (particlesVectorBegining->getBelief() < BELIEF_THRESHOLD && _particleVector.size() > 1)
		{
			_particleVector.erase(particlesVectorBegining);
		}
		else
		{
			goodParticlesCounter++;

			if (goodParticlesCounter % 15 == 0)
			{
				Map particleMap = particlesVectorBegining->getMap();
				particleMap.printMap();

				cout << endl << endl;

				goodParticlesCounter = 0;
			}

			if(_particleVector.size() < PARTICLES_MAX_QUANTITY)
			{
				Location* particleLocation = particlesVectorBegining->getLocation();

				Particle newParticle(particleLocation->getX(),particleLocation->getY());
				newParticle.setYaw(particleLocation->getYaw());
				newParticle.setMap(particlesVectorBegining->getMap());

				_particleVector.push_back(newParticle);

				delete particleLocation;
			}
		}

		particlesVectorBegining++;
	}
}

SlamManager::~SlamManager()
{
}
