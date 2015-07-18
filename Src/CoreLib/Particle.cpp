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
#include <libplayerc++/playerc++.h>

using namespace CoreLib;
using namespace PlayerCc;
//Constructors of objects type of Particle
Particle::Particle(float x, float y, float yaw, float belief){
	//cout << "beginning ctor" << endl;
	//cout << x << "    " << y << "     " << yaw << "    " << belief;
	pX = x;
	pY = y;
	pYaw = yaw;
	pBelief = belief;
	//cout << "ending ctor" << endl;
}

//Method which handles the particle position update
void Particle::UpdateParticle(float delX, float delY, float delYaw, float* laserScan, int laserCount,LaserProxy* lp) {
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
	pBelief *=  /* ProbCalc(delX, delY, delYaw) */ ProbUpdateMapByScan(laserScan,laserCount,lp);
	cout << " after ProbUpdateMapByScan" << endl;
}

//Method which calculate the particle's probability by map
float Particle::ProbUpdateMapByScan(float* laserScan, int laserCount,LaserProxy* lp) {
	Cell* CheckedCell;
	float xObj,yObj;
	int mismatch = 0;
	int match = 0;
	int i,j;
	unsigned X;
	unsigned Y;

	for (i=0; i<laserCount;i++)
	{
		//INDEX_PER_DEGREE) {
		// the sensor detects that the road is open
		//cout << "scan " << i << " in range "<< laserScan[i] << endl;

		if (laserScan[i] < lp->GetMaxRange()) {
			//cout << "the laser scan tells its open" << endl;
			for (j=SENSOR_FROM_END; j<=SENSOR_DETECTION_RANGE; j = j+CELL_DIM) {
				xObj = pX + laserScan[i] * cos(pYaw + lp->GetBearing(i));
				yObj = pY + laserScan[i] * sin(pYaw + lp->GetBearing(i));

				//xObj = (j * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
				//yObj = (j * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
				//cout << "before anything: x=" << pX << "   y:" << pY << "     yaw=" <<pYaw << endl;
				//cout << "numbers before RobotRelativeXPosToPixelXCoord: X=" << yObj << "    Y=" <<  xObj << endl;
				X = CordinateConvert::RobotRelativeYPosToPixelYCoord(yObj, 10, SimManager::GetInstance()->m_Map->getCols());
				Y = CordinateConvert::RobotRelativeXPosToPixelXCoord(xObj, 10, SimManager::GetInstance()->m_Map->getRows());
				//cout << "new numbers after RobotRelativeXPosToPixelXCoord: X=" << Y << "    Y=" <<  X << endl;
				CheckedCell = SimManager::GetInstance()->m_Map->getCell(Y, X);
				if(CheckedCell != NULL && CheckedCell->isCellWalkable()) // the cell is open (like the laser detects)
				 {
					match++;
					//cout << "match!" << endl;
				 }
				else
				 {
					 mismatch++;
					// cout << "mismatch!" << endl;
				 }
			}
		// the laser detects that the road is closed
		} /*else {
			cout << "the laser scan tells its closed" << endl;

			xObj = pX;//((M_TO_CM(laserScan[i])) * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pX;
			yObj = pY;//((M_TO_CM(laserScan[i])) * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pY;
			unsigned X = CordinateConvert::RobotRelativeYPosToPixelYCoord(yObj, 10, SimManager::GetInstance()->m_Map->getCols());
			unsigned Y = CordinateConvert::RobotRelativeXPosToPixelXCoord(xObj, 10, SimManager::GetInstance()->m_Map->getRows());
			cout<< "xObj = " << Y << "	" << "yObj= " << X << endl;
			if (SimManager::GetInstance()->m_Map->getCell(Y,X)->isCellWalkable()) // the cell is open (and the laser detects otherwise)
			{
				mismatch++;
				 cout << "mismatch!" << endl;
			}
			else{
				match++;
				 cout << "match!" << endl;
			}
		} */
	}

	if ((mismatch + match) == 0)
		return (float) 0;
	else
	{
		float newBel = (float)(match)/(mismatch + match);
		cout << "matched:" << match << "	" << "mismatch: " << mismatch << endl;
		cout << "new belief:" << newBel << endl;
		return newBel;
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
	pX = NULL;
	pY = NULL;
	pYaw = NULL;
	pBelief = NULL;

}
