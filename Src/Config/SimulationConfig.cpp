#include "SimulationConfig.h"

#include <string>

#include "../../Libs/ConfigParser/Config.h"
#include "FileConfig.h"

using namespace std;

namespace config
{

	SimulationConfig::SimulationConfig(const char* cfgFilePath)
	{
		Config configParser = Config(cfgFilePath);

		// TODO Move entry names to Conf.h
		m_PngMapPath = configParser.pString(CFG_FILE_PATH);
		m_StartLocation.X = configParser.pDouble(CFG_START_LOCATION_X_CM);
		m_StartLocation.Y = configParser.pDouble(CFG_START_LOCATION_Y_CM);
		m_StartLocation.Yaw = configParser.pDouble(CFG_START_LOCATION_YAW);
		m_EndLocation.X = configParser.pDouble(CFG_END_LOCATION_X_CM);
		m_EndLocation.Y = configParser.pDouble(CFG_END_LOCATION_Y_CM);
		m_PixelResolution = configParser.pDouble(CFG_PIXEL_WORLD_RESOLUTION);
		m_GridResolution = configParser.pDouble(CFG_GRID_WORLD_RESOLUTION);
		m_RobotSize.Width = configParser.pDouble(CFG_ROBOT_SIZE_WIDTH_CM);
		m_RobotSize.Height = configParser.pDouble(CFG_ROBOT_SIZE_HEIGHT_CM);
	}

	SimulationConfig::~SimulationConfig()
	{
	}

	string SimulationConfig::getPngMapPath()
	{
		return m_PngMapPath;
	}

	RobotLocation SimulationConfig::getRobotStartLocation()
	{
		return m_StartLocation;
	}

	RobotLocation SimulationConfig::getRobotEndLocation()
	{
		return m_EndLocation;
	}

	float SimulationConfig::getPixelResolution()
	{
		return m_PixelResolution;
	}

	float SimulationConfig::getGridResolution()
	{
		return m_GridResolution;
	}

	Size SimulationConfig::getRobotSize()
	{
		return m_RobotSize;
	}

}
