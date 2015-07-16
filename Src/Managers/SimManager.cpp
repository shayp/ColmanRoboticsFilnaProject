#include "SimManager.h"
#include <math.h>
#include "../AStar/FindPath.h"
#include "WayPointManager.h"
#include "../Config/Config.h"

using namespace Utils;

 SimManager* SimManager::pInstance = NULL;

SimManager* SimManager::GetInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new SimManager();
	}

	return pInstance;
}
SimManager::SimManager()
{
	m_wpManager = new WaypointManager();
}

bool SimManager::Init(const char* cfgFilePath)
{
	m_Config = new SimulationConfig(cfgFilePath);

	m_BlownMap = NULL;
	m_Map = NULL;
}

SimManager::~SimManager()
{
	delete m_Config;
	m_Config = NULL;

	delete m_BlownMap;
	m_BlownMap = NULL;

	delete m_Map;
	m_Map = NULL;
}

void SimManager::run()
{
	BuildMap();

	vector<Cell*> WayPoints = RunAStar();

	if (m_wpManager->SetPath(WayPoints,  DEFAULT_WAYPOINT_RESOLUTION, DEFAULT_WAYPOINT_ACCURACY) == true)
	{
		vector<Cell*> Path = m_wpManager->GetAllWayPoints();
		for (Cell* PathCell : Path)
		{
			if (PathCell != NULL)
			{
				m_BlownMap->getCell(PathCell->m_loc.X, PathCell->m_loc.Y)->SetAsWayPoint(ePathWayPoint);
			}
		}
	}
	else
	{
		printf("/nError setting path from A Star/n");
	}

	string mapFilename = m_Config->getPngMapPath();

	// Create map
	float pixelsPerOneGrid = m_Config->getGridResolution() / m_Config->getPixelResolution();

	int indexOfMapExt = mapFilename.find_last_of(".");
	string WayPointsMapFilename = string(mapFilename).insert(indexOfMapExt, "_waypoints");

	// Save map with weights and waypoints
	MapUtils::mapToPng(m_BlownMap, pixelsPerOneGrid, WayPointsMapFilename);

}
void SimManager::BuildMap()
{
	string mapFilename = m_Config->getPngMapPath();

	// Create map
	float pixelsPerOneGrid = m_Config->getGridResolution() / m_Config->getPixelResolution();
	m_Map = MapUtils::pngToMap(mapFilename, pixelsPerOneGrid);

	// Create blown map
	int indexOfMapExt = mapFilename.find_last_of(".");
	string blowMapFilename = string(mapFilename).insert(indexOfMapExt, "_blown");

	float robotMaxDimnsionCm = std::max(m_Config->getRobotSize().Width, m_Config->getRobotSize().Height);
	unsigned robotMaxDimensionsPx = (unsigned) ceil(robotMaxDimnsionCm / m_Config->getPixelResolution() / 2);
	PngUtils::blowMap(mapFilename, robotMaxDimensionsPx, blowMapFilename);

	// Load the blown map to memory
	m_BlownMap = MapUtils::pngToMap(blowMapFilename, pixelsPerOneGrid);

	// Allow Smooth paths
	MapUtils::addMapWeights(m_BlownMap);

	string mapWithWeight = string(blowMapFilename).insert(indexOfMapExt, "_weight");

	// Save map with weights
	MapUtils::mapToPng(m_BlownMap, pixelsPerOneGrid, mapWithWeight);

}

vector<Cell*> SimManager::RunAStar()
{
	FindPath* pathFinder = new FindPath(m_BlownMap);
	Cell* StartLocation = new Cell(m_Config->getRobotStartLocation().X, m_Config->getRobotStartLocation().Y);
	Cell* EndLocation = new Cell(m_Config->getRobotEndLocation().X, m_Config->getRobotEndLocation().Y);
	return pathFinder->search(StartLocation, EndLocation);

}

vector<Cell*> SimManager::GetAllWayPoints()
{
	return m_wpManager->GetAllWayPoints();
}

