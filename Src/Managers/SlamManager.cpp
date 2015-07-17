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
	Particle* newP = new Particle(xRobot,yRobot,yawRobot,1.0);
	particles.clear();
	particles.push_back(*newP);
	cout<<"-----------------------------------"<<endl;	
	cout<<"First Particle Created! his coordinates are:"<<endl;
	cout<<"-----------------------------------"<<endl;
	cout << "X:"<< particles.begin()->GetX() << "     " <<"Y:" << particles.begin()->GetY() << "    " << "Yaw:" << particles.begin()->GetYaw()<< endl;
}

//Method which gives the ability to update all particles which are stored in the vector
void SlamManager::UpdateParticles(float delX, float delY, float delTetha,float laserScan[], int laserCount,LaserProxy* lp) {
	cout << "begins UpdateParticles, the list of particles exist now are:" << endl;
	PrintParticles();
	particlesVec::iterator pCurr = particles.begin();
	particlesVec::iterator pEnd = particles.end();
		for (int q=0; q < particles.size(); pCurr++)
		{
			q++;
			//cout << "begins to update pCurr particle" << endl;
			pCurr->UpdateParticle(delX,delY, delTetha,laserScan,laserCount,lp);
			cout << "finished to update pCurr particle" << endl;
			if (pCurr->GetBelief() < THRESH_LOW)
			{
				cout << "==================================" << endl;
				 cout << "DELETING PARTICLE!!!" << endl;
				 pCurr->PrintParticle();
				 cout << "==================================" << endl;
				particles.erase(pCurr);
				cout << "Erase finished successfully " << endl;
				if (particles.size() == 0){
					cout << "0 PARTICLES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
					//exit(1);
				}
			}
			else if ((pCurr->GetBelief() > THRESH_HIGH) && (particles.size() < PART_COUNT)) {
				for(int q=0; q < 3; q++){
					 double randX = ((double) rand() / (RAND_MAX)) * RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
					 double randY = ((double) rand() / (RAND_MAX)) * RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
					 double randYaw = ((double) rand() / (RAND_MAX)) * RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
					 cout << "===============================================" <<endl;
					 cout << "CREATING NEW PARTICLE!!!" <<endl;
					 cout << "coordinates: of old particle:" << endl;
					 pCurr->PrintParticle();
					 Particle* newP = new Particle(pCurr->GetX() + randX,pCurr->GetY() + randY,pCurr->GetYaw() + randYaw,1.0);
					 if (newP == NULL) {
						 cout << "newP IS NULL!!!!!!!!!!!!!" << endl;
					 }
					 cout << "coordinates of new particle:" << endl;
					 newP->PrintParticle();
					 cout << "===============================================" <<endl;
					 //newP.PrintParticle();
					 particles.push_back(*newP);
				}
			}
		}

	}

//Method which print the best particle
bool SlamManager::GetLocationByParticles(double &x,double &y,double &yaw) {

	cout << "number of particles: " << particles.size() << endl;
	// Finds the best particle
	Particle pBest = particles[0];

	for(int i=1; i < particles.size(); i++){
		if (particles[i].pBelief > pBest.pBelief){
			pBest = particles[i];
		}
	}
	cout << "found best particle: "  << endl;
	pBest.PrintParticle();
	if (pBest.pBelief < THRESH_LOW)
	{
		return false;
	}
	else{
		x = pBest.GetX();
		y= pBest.GetY();
		yaw = pBest.GetYaw();
		return true;
	}
	}

//Destructor of objects type of SlamManager
SlamManager::~SlamManager() {
}
