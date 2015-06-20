#include "SimManager.h"
#include <math.h>
using namespace Utils;

SimManager::SimManager(const char* cfgFilePath)
{
	m_Config = new SimulationConfig(cfgFilePath);

	m_Map = NULL;
	m_BlownMap = NULL;
}

SimManager::~SimManager()
{
	delete m_Config;
	m_Config = NULL;

	delete m_Map;
	m_Map = NULL;

	delete m_BlownMap;
	m_BlownMap = NULL;
}

void SimManager::run()
{
	BuildMap();
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
}
