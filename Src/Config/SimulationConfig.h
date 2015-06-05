#pragma once

#include <string>

using namespace std;
using namespace CoreLib;

namespace config {

class SimulationConfig
{
	public:
		SimulationConfig(string cfgFilePath);
		virtual ~SimulationConfig();

		string getPngMapPath();
		RobotLocation getRobotStartLocation();
		RobotLocation getRobotEndLocation();
		float getPixelResolution();
		float getGridResolution();
		Size getRobotSize();

	private:
		string m_PngMapPath;
		RobotLocation m_StartLocation;
		RobotLocation m_EndLocation;
		float m_PixelResolution;
		float m_GridResolution;
		Size m_RobotSize;
};
}
