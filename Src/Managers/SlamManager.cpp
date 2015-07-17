/*
 * SlamManager.cpp
 */

#include "SlamManager.h"
#include <iostream>
using namespace CoreLib;
using namespace std;

//Constructor SlamManager
SlamManager::SlamManager(float xRobot,float yRobot,float yawRobot) {
	srand(time(NULL));
	InitParticles(xRobot,yRobot,yawRobot);
}

//Initiation method -  Creates one particle in the given location
void SlamManager::InitParticles(float xRobot,float yRobot,float yawRobot) {
	Particle newP(xRobot,yRobot,yawRobot);
	particles.clear();
	particles.push_back(newP);
	cout<<"-----------------------------------"<<endl;	
	cout<<"First Particle Created!"<<endl;
	cout<<"-----------------------------------"<<endl;
}

//Method which gives the ability to update all particles which are stored in the vector
void SlamManager::UpdateParticles(float delX, float delY, float delTetha,float laserScan[], int laserCount) {
	//cout << "begins to update particles" << endl;
	particlesVec::iterator pCurr = particles.begin();
	pCurr->PrintParticle();
	particlesVec::iterator pEnd = particles.end();
	pEnd->PrintParticle();
	if (pCurr != pEnd) {
		for (; pCurr!=pEnd; pCurr++ ) {
			//cout << "begins to update pCurr particle" << endl;
			pCurr->UpdateParticle(delX,delY, delTetha,laserScan,laserCount);
			cout << "finished to update pCurr particle" << endl;
			if (pCurr->GetBelief() < THRESH_LOW)
				particles.erase(pCurr);
			else if ((pCurr->GetBelief() > THRESH_HIGH) && (particles.size() < PART_COUNT)) {
					 int randX = std::rand() % (-RADIUS/2) + (RADIUS/2);
					 int randY = std::rand() % (-RADIUS/2) + (RADIUS/2);
					 int randYaw = std::rand() % (-RADIUS/2) + (RADIUS/2);

					 Particle newP(pCurr->pX + randX,pCurr->pY + randY,pCurr->pYaw + randYaw);
					 particles.push_back(newP);
			}
		}

	}
}

//Method which print the best particle
void SlamManager::GetLocationByParticles(float &x,float &y,float &yaw) {

	// Finds the best particle
	Particle pBest = particles[0];

	for(int i=1; i < particles.size(); i++){
		if (particles[i].pBelief > pBest.pBelief){
			pBest = particles[i];
		}
	}
		x = pBest.GetX();
		y= pBest.GetY();
		yaw = pBest.GetYaw();
	}

//Destructor of objects type of SlamManager
SlamManager::~SlamManager() {

}
