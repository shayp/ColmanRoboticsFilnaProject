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

		static SimManager* GetInstance();
		bool Init(const char* cfgFilePath);
		void run();
		Map* m_Map;

	private:
		SimManager();
		virtual ~SimManager();
		SimulationConfig* m_Config;
		static SimManager* pInstance;
		Map* m_BlownMap;

		void BuildMap();
		vector<Cell*> RunAStar();

};

#endif SIM_MANAGER_H
