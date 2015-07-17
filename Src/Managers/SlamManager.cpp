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
	Particle* newP = new Particle(xRobot,yRobot,yawRobot);
	particles.clear();
	particles.push_back(*newP);
	cout<<"-----------------------------------"<<endl;	
	cout<<"First Particle Created! his coordinates are:"<<endl;
	cout<<"-----------------------------------"<<endl;
	cout << "X:"<< particles.begin()->GetX() << "     " <<"Y:" << particles.begin()->GetY() << "    " << "Yaw:" << particles.begin()->GetYaw()<< endl;
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
			{
				 cout << "DELETING PARTICLE!!!" << endl;
				particles.erase(pCurr);
			}
			else if ((pCurr->GetBelief() > THRESH_HIGH) && (particles.size() < PART_COUNT)) {
				for(int q=0; q < 3; q++){
					 double randX = (double)rand()/(RAND_MAX+1)*(RADIUS-0)+RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
					 double randY = (double)rand()/(RAND_MAX+1)*(RADIUS-0)+RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
					 double randYaw = (double)rand()/(RAND_MAX+1)*(RADIUS-0)+RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
					 cout << "CREATING NEW PARTICLE!!!" <<endl;
					 cout << "old coordinate:" << endl;
					 cout<< "X:" << pCurr->pX << "  " << "Y:" << pCurr->pY << "     " << "yaw:" << pCurr->pYaw << endl;
					 Particle newP(pCurr->pX + randX,pCurr->pY + randY,pCurr->pYaw + randYaw);
					 newP.PrintParticle();
					 particles.push_back(newP);
				}
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
	if (pBest.pBelief < THRESH_LOW)
	{
		x = 0;
		y = 0;
		yaw = 0;
	}
		x = pBest.GetX();
		y= pBest.GetY();
		yaw = pBest.GetYaw();
	}

//Destructor of objects type of SlamManager
SlamManager::~SlamManager() {

}
