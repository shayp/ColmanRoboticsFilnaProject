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
#include "../Utils/CordianteConverter.h"

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
	cout << " THE COORDINATES BEFORE ADDING DELTA:" << endl;
	cout << pX << "  " << pY << "  " << pYaw << endl;
	// moving the particle with the same estimated vector that the robot itself moved
	pX += delX;
	pY += delY;
	pYaw += delYaw;
	cout << "THE COORDINATES AFTER ADDING DELTA: "<< endl;
	cout << pX << "  " << pY << "  " << pYaw << endl;
	// updating the belief of the new location!
	cout << " before ProbUpdateMapByScan" << endl;
	pBelief *=  /* ProbCalc(delX, delY, delYaw) */ ProbUpdateMapByScan(laserScan,laserCount);
	cout << " after ProbUpdateMapByScan" << endl;
}

//Method which calculate the particle's probability by map
float Particle::ProbUpdateMapByScan(float laserScan[], int laserCount) {
	float xObj,yObj;
	int mismatch = 0;
	int match = 0;
	int i,j;

	for (i=0; i<laserCount; i = i+INDEX_PER_DEGREE) {
		// the sensor detects that the road is open
		if (laserScan[i] > OPEN_PATH_RANGE) {
			cout << "the laser scan tells its open" << endl;
			for (j=SENSOR_FROM_END; j<=SENSOR_DETECTION_RANGE; j = j+CELL_DIM) {
				//cout << "inside j for" << endl;
				xObj = pX;//(j * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
				//cout << "after xObj" << endl;
				yObj = pY;//(j * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
				cout << "numbers before RobotRelativeXPosToPixelXCoord: X=" << pX << "    Y=" <<  pY << endl;
				// TODO: Change to grid resplution instead of 10
				unsigned X = CordinateConvert::RobotRelativeYPosToPixelYCoord(yObj, 10, SimManager::GetInstance()->m_Map->getCols());
				unsigned Y = CordinateConvert::RobotRelativeXPosToPixelXCoord(xObj, 10, SimManager::GetInstance()->m_Map->getRows());
				cout << "new numbers after RobotRelativeXPosToPixelXCoord: X=" << X << "    Y=" <<  Y << endl;
				if(SimManager::GetInstance()->m_Map->getCell(X, Y)->isCellWalkable()) // the cell is open (like the laser detects)
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

			xObj = pX;//((M_TO_CM(laserScan[i])) * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
			yObj = pY;//((M_TO_CM(laserScan[i])) * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
			unsigned X = CordinateConvert::RobotRelativeXPosToPixelXCoord(yObj, 10, SimManager::GetInstance()->m_Map->getCols());
			unsigned Y = CordinateConvert::RobotRelativeXPosToPixelXCoord(xObj, 10, SimManager::GetInstance()->m_Map->getRows());
			cout<< "xObj = " << xObj << "	" << "yObj= " << yObj << endl;
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
	{
		cout << "matched:" << match << "	" << "mismatch: " << mismatch << endl;
		return ((float)(match))/(mismatch + match);
	}

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
