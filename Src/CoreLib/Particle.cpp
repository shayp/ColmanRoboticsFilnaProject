/*
 * Particle.cpp
 *
 */

#include "Particle.h"
#include <stdio.h>
#include <cmath>
#include <iostream>

#include "../RobotAPI/Helper.h"
#include "../Managers/SimManager.h"
#include "../Utils/CordianteConverter.h"
#include "Cell.h"

using namespace CoreLib;
using namespace PlayerCc;

//Constructors of objects type of Particle
Particle::Particle(float x, float y, float yaw, float belief) {
	pX = x;
	pY = y;
	pYaw = yaw;
	pBelief = belief;
}

//Method which handles the particle position update
void Particle::UpdateParticle(float delX, float delY, float delYaw,
		float* laserScan, int laserCount, LaserProxy* lp) {
	// moving the particle with the same estimated vector that the robot itself moved
	pX += delX;
	pY += delY;
	pYaw += delYaw;
	// updating the belief of the new location!
	SetBelief(NORMALIZEDFACTOR * ProbUpdateByScan(laserScan, laserCount, lp));
}

//Method which calculate the particle's probability by map
float Particle::ProbUpdateByScan(float* laserScan, int laserCount,
		LaserProxy* lp) {
	Cell* CheckedCell;
	float xObj, yObj;
	int match = 0;
	unsigned X;
	unsigned Y;

	for (int i = 0; i < laserCount; i += 3) {
		if (laserScan[i] < lp->GetMaxRange()) {
			xObj = pX + laserScan[i] * cos(pYaw + lp->GetBearing(i));
			yObj = pY + laserScan[i] * sin(pYaw + lp->GetBearing(i));

			X = CordinateConvert::RobotRelativeYPosToPixelYCoord(yObj, 10,
					SimManager::GetInstance()->m_Map->getCols());
			Y = CordinateConvert::RobotRelativeXPosToPixelXCoord(xObj, 10,
					SimManager::GetInstance()->m_Map->getRows());
			if (CheckedCell == NULL) {
				cout << "====================================" << endl;
				cout << "CELL OUT OF RANGE!:" << endl;
				cout << "coordinates:" << pX << "    " << pY << "      " << pYaw
						<< endl;
				cout << "after conversion:" << X << "    " << Y << endl;
				cout << "====================================" << endl;
			}
			if (CheckedCell != NULL && CheckedCell->isCellWalkable()) // the cell is open (like the laser detects)
					{
				match++;
			}
		}
	}
	return (float) (match) / (laserCount / 3);
}

//Method which return the particle Belief value
double Particle::GetBelief() {
	return pBelief;
}

//Method which return the particle X value
double Particle::GetX() {
	return pX;
}

//Method which return the particle Y value
double Particle::GetY() {
	return pY;
}

//Method which return the particle Yaw value
double Particle::GetYaw() {
	return pYaw;
}

//Method which converts laser index to angle
float Particle::ConverteIndexToAngle(int index, int x, int radius) {
	if (x == 0)
		return 0;
	return ((float) index * ((float) radius / x)) - radius / 2.0;
}

//Destructor of objects type of Particle
Particle::~Particle() {
	pX = NULL;
	pY = NULL;
	pYaw = NULL;
	pBelief = NULL;

}
