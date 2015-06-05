#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

#include "Particle.h"

Particle::Particle(double x,double y)
{
	Location* _location = new Location();

	_location->setX((double)(rand() % 30) - PARTICLE_CLOUD_RADIUS + x);
	_location->setY((double)(rand() % 30) - PARTICLE_CLOUD_RADIUS + y);
	_location->setYaw(Helper::IndexToRadians(rand()/Helper::TOTAL_SCAN_SPAN));
	_belief = 1.0;

	int mapX,mapY;

	_map.getMapCoordinates(_location->getX(),_location->getY(),mapX,mapY);
	for (int i=-ROBOT_DIMENTION_ON_MAP; i<ROBOT_DIMENTION_ON_MAP; i++)
		for (int j=-ROBOT_DIMENTION_ON_MAP; j<ROBOT_DIMENTION_ON_MAP; j++)
			_map.setCellValue(mapX+i, mapY+j, Helper::FREE_CELL);
}

void Particle::updateParticle(double deltaX, double deltaY, double deltaYaw, float laserScan[])
{
	_location.setX(_location.getX() + deltaX);
	_location.setY(_location.getY() + deltaY);
	_location.setYaw(_location.getYaw()+deltaYaw);

	double predictionBelief = _belief * calculatePrediction(deltaX, deltaY, deltaYaw);
	_belief =  predictionBelief * probabilityUpdateMapUsingScan(laserScan);
}

double Particle::probabilityUpdateMapUsingScan(float laserScan[])
{
	int countMiss = 0;
	int countHit = 0;

	for (int i=0; i < Helper::TOTAL_SCAN_SPAN; i += Helper::DEGREES_INDEX_RATIO)
	{
		if (laserScan[i] > OPEN_PATH_RANGE)
		{
			updateCellRangeToFree(i, Helper::MetersToCentimeters(OPEN_PATH_RANGE), countHit, countMiss);
		}
		else
		{
			updateCellRangeToFree(i, Helper::MetersToCentimeters(laserScan[i]),  countHit,  countMiss);
		    updateCellToOccupied(laserScan, i, countHit, countMiss);
		}
	}

	return ((float)(countHit))/(countMiss + countHit);
}

void Particle::updateCellRangeToFree(int laserIndex, double range, int &countHit, int &countMiss)
{
    for (int j = SENSOR_FROM_END; j < range; j = j + Helper::MAP_RESOLUTION)
	{
		double objectX = (j * cos(Helper::IndexToRadians(laserIndex) + _location.getYaw())) + _location.getX();
		double objectY = (j * sin(Helper::IndexToRadians(laserIndex) + _location.getYaw())) + _location.getY();

		int objectXOnMap,objectYOnMap;
		_map.getMapCoordinates(objectX,objectY,objectXOnMap,objectYOnMap);

		int cellValue = _map.getCellValue(objectXOnMap,objectYOnMap);

		if (cellValue != Helper::FREE_CELL)
		{
			_map.setCellValue(objectXOnMap,objectYOnMap, Helper::FREE_CELL);
		}

		if (cellValue == Helper::OCCUPIED_CELL)
		{
			countMiss++;
		}
		else
		{
			countHit++;
		}
	}
}

void Particle::updateCellToOccupied(float laserScan[], int i, int &countHit, int &countMiss)
{
    double objectX = (Helper::MetersToCentimeters(laserScan[i]) * cos(Helper::IndexToRadians(i)) + _location.getYaw()) + _location.getX();
    double objectY = (Helper::MetersToCentimeters(laserScan[i]) * sin(Helper::IndexToRadians(i)) + _location.getYaw()) + _location.getY();

    int objectXOnMap,objectYOnMap;
    _map.getMapCoordinates(objectX, objectY, objectXOnMap, objectYOnMap);

    int cellValue = _map.getCellValue(objectXOnMap,objectYOnMap);

    if(cellValue != Helper::OCCUPIED_CELL)
    {
    	_map.setCellValue(objectXOnMap, objectYOnMap, Helper::OCCUPIED_CELL);
    }

    if(cellValue == Helper::FREE_CELL)
    {
    	countMiss++;
    }
    else
    {
    	countHit++;
    }
}

double Particle::calculatePrediction(double deltaX, double deltaY, double deltaYaw)
{
	double distance = sqrt(pow(deltaX,2)+pow(deltaY,2));

	if ((deltaYaw <= NORMAL_ACCURATE_ANGLE_TO_MOVE) && (deltaYaw >= -NORMAL_ACCURATE_ANGLE_TO_MOVE))
	{
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance + 0.2);
	}
	else if ((deltaYaw < MAX_ACCURATE_ANGLE_TO_MOVE) && (deltaYaw > -MAX_ACCURATE_ANGLE_TO_MOVE))
	{
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance - 0.2);
	}
	else
		return 1.0;
}

void Particle::setMap(Map map)
{
	_map = map;
}

Map Particle::getMap()
{
	return _map;
}

double Particle::getBelief()
{
	return _belief;
}

void Particle::printMap()
{
	_map.printMap();
}

void Particle::setYaw(double yaw)
{
	_location.setYaw(yaw);
}

Location* Particle::getLocation()
{
	return new Location(_location.getX(),_location.getY(),_location.getYaw());
}

Particle::~Particle()
{
}
