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
	cout << "NEW particle!" << endl;
	particles.clear();
	particles.push_back(newP);
	cout<<"-----------------------------------"<<endl;	
	cout<<"First Particle Created! his coordinates are:"<<endl;
	cout<<"-----------------------------------"<<endl;
	cout << "X:"<< particles[0]->GetX() << "     " <<"Y:" << particles[0]->GetY() << "    " << "Yaw:" << particles[0]->GetYaw()<< endl;
}

//Method which gives the ability to update all particles which are stored in the vector
void SlamManager::UpdateParticles(float delX, float delY, float delTetha,float* laserScan, int laserCount,LaserProxy* lp)
{
	vector<int> childsToRemove;
	vector<Particle*> childsToAdd;
	unsigned index = 0;
	int q=0;
	double randX, randY, randYaw;
	Particle* newP;
	cout << "begins UpdateParticles, the list of particles exist now are:" << endl;
	//PrintParticles();

	if (particles.size() == 0)
	{

		cout << "There are no more particles, bye bye!" << endl;
		exit(1);
	}
	cout << "** particle size before update ** " << particles.size() << endl;
	for (Particle* pCurrent: particles)
	{
		pCurrent->UpdateParticle(delX,delY, delTetha,laserScan,laserCount,lp);
		cout << "finished to update pCurr particle" << endl;
		if (pCurrent->GetBelief() < THRESH_LOW)
		{
			childsToRemove.push_back(index);
		}
		else if ((pCurrent->GetBelief() > THRESH_LOW) && (particles.size() < PART_COUNT))
		{
			 cout << "coordinates: of old particle:" << endl;
			 pCurrent->PrintParticle();
			for(q=0; q < 3; q++)
			{
				 randX = ((double) rand() / (RAND_MAX)) * RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
				 randY = ((double) rand() / (RAND_MAX)) * RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
				 randYaw = ((double) rand() / (RAND_MAX)) * RADIUS; //std::rand() % (-RADIUS/2) + (RADIUS/2);
				 //cout << "===============================================" <<endl;
				 //cout << "CREATING NEW PARTICLE!!!" <<endl;
				 newP = new Particle(pCurrent->GetX() + randX,pCurrent->GetY() + randY,pCurrent->GetYaw() + randYaw,1.0);
				 //cout << "coordinates of new particle:" << endl;
				 //newP->PrintParticle();
				 //cout << "===============================================" <<endl;
				 childsToAdd.push_back(newP);
			}
		}

		index++;
	}
	if (childsToRemove.size() > 0)
	{
		cout << "There are " << childsToRemove.size() << " particales to remove" << endl;
		for(int i = childsToRemove.size() - 1; i>=0; i--)
		{
			int indexToRemove = childsToRemove[i];
			particles.erase(particles.begin() + indexToRemove);
		}
	}
	if (childsToAdd.size() > 0)
	{
		cout << "There are " << childsToAdd.size() << " particales to add" << endl;
		for(int i = 0; i < childsToAdd.size(); i++)
		{
			particles.push_back(childsToAdd[i]);
		}
	}

	cout << "** particle size after update ** " << particles.size() << endl;
}

//Method which print the best particle
bool SlamManager::GetLocationByParticles(double &x,double &y,double &yaw) {

	cout << "number of particles: " << particles.size() << endl;
	// Finds the best particle
	Particle* pBest = particles[0];

	for(int i=1; i < particles.size(); i++){
		if (particles[i]->pBelief > pBest->pBelief){
			pBest = particles[i];
		}
	}
	cout << "found best particle: "  << endl;
	pBest->PrintParticle();
	if (pBest->pBelief < THRESH_LOW)
	{
		return false;
	}
	else{
		x = pBest->GetX();
		y= pBest->GetY();
		yaw = pBest->GetYaw();
		return true;
	}
	}

//Destructor of objects type of SlamManager
SlamManager::~SlamManager() {
}
