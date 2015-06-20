#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include "../CoreLib/Map.h"
#include "../Config/SimulationConfig.h"
#include "../Utils/MapUtils.h"
#include "../Utils/PngUtils.h"
using namespace CoreLib;
using namespace config;

class SimManager
{
	public:
		SimManager(const char* cfgFilePath);
		virtual ~SimManager();

		void run();

	private:
		SimulationConfig* m_Config;
		Map* m_Map;
		Map* m_BlownMap;

		void BuildMap();
};

#endif SIM_MANAGER_H
