/*
 * Particle.cpp
 *
 */

#include "Particle.h"
#include "../Managers/SimManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

using namespace CoreLib;

//Constructors of objects type of Particle
Particle::Particle(float x,float y) {
	Particle(x,y,0);
}
Particle::Particle(float x,float y,float yaw) {
	Particle(x,y,yaw,1.0);
}
Particle::Particle(float x, float y, float yaw, float belief){
	pX = x;
	pY = y;
	pYaw = yaw;
	pBelief = belief;
}

//Method which handles the particle position update
void Particle::UpdateParticle(float delX, float delY, float delYaw, float laserScan[], int laserCount) {
	cout << " Inside UpdateParticle, before M_TO_CM" << endl;
	cout << pX << "  " << pY << "  " << pYaw << endl;
	// moving the particle with the same estimated vector that the robot itself moved
	pX += delX;
	pY += delY;
	pYaw += delYaw;
	cout << " Inside UpdateParticle, after M_TO_CM:" << endl;
	cout << pX << "  " << pY << "  " << pYaw << endl;
	// updating the belief of the new location!
	cout << " before ProbUpdateMapByScan" << endl;
	pBelief *=  /* ProbCalc(delX, delY, delYaw) */ ProbUpdateMapByScan(laserScan,laserCount);
	cout << " after ProbUpdateMapByScan" << endl;
}

//Method which calculate the particle's probability by map
float Particle::ProbUpdateMapByScan(float laserScan[], int laserCount) {
	cout << laserCount << endl;
	cout << "begins ProbUpdateMapByScan" << endl;
	float xObj,yObj;
	int mismatch = 0;
	int match = 0;
	int i,j;

	for (i=0; i<laserCount; i = i+INDEX_PER_DEGREE) {
		//cout << "inside for" << endl;
		// the sensor detects that the road is open
		if (laserScan[i] > OPEN_PATH_RANGE) {
			cout << "open" << endl;
			for (j=SENSOR_FROM_END; j<=SENSOR_DETECTION_RANGE; j = j+CELL_DIM) {
				//cout << "inside j for" << endl;
				xObj = (j * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
				//cout << "after xObj" << endl;
				yObj = (j * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
				//cout << "after yObj" << endl;
				cout << "before trimming:" << endl;
				cout<< "xObj = " << xObj << "	" << "yObj= " << yObj << endl;
				cout << "after trimming: " ;
				xObj = (int)xObj;
				yObj = (int) yObj;
				cout << xObj << "   " << yObj << endl;
				//if(SimManager::GetInstance()->m_Map->getCell(xObj,yObj))
				if(SimManager::GetInstance()->m_Map->getCell(xObj,yObj)->isCellWalkable()) // the cell is open (like the laser detects)
				 {
					match++;
					cout << "match!" << endl;
				 }
				else
				 {
					 mismatch++;
					 cout << "mismatch!" << endl;
				 }
			}
		// the laser detects that the road is closed
		}else {
			cout << "closed" << endl;
			xObj = ((M_TO_CM(laserScan[i])) * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
			yObj = ((M_TO_CM(laserScan[i])) * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
			if (SimManager::GetInstance()->m_Map->getCell(xObj,yObj)->isCellWalkable()) // the cell is open (and the laser detects otherwise)
			{
				mismatch++;
				 cout << "mismatch!" << endl;
			}
			else{
				match++;
				 cout << "match!" << endl;
			}
		}
	}

	if ((mismatch + match) == 0)
		return (float) 0;
	else
		return ((float)(match))/(mismatch + match);

}

//Method which calculate the particle's probability
float Particle::ProbCalc(float delX, float delY, float delYaw) {
	float distance = sqrt(pow(delX,2)+pow(delY,2));
	if ((delYaw < NORMAL_ACCURATE_ANGLE_TO_MOVE) && (delYaw > -NORMAL_ACCURATE_ANGLE_TO_MOVE)) {
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance + 0.2);
	}
	else if ((delYaw < MAX_ACCURATE_ANGLE_TO_MOVE) && (delYaw > -MAX_ACCURATE_ANGLE_TO_MOVE))
	{
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance - 0.2);
	}
	return 1.0;
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
	return ((float)index*((float)radius/x))-radius/2.0;
}

//Destructor of objects type of Particle
Particle::~Particle() {
}
