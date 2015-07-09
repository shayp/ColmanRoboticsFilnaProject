#ifndef WAYPOINT_MANAGER_H
#define WAYPOINT_MANAGER_H



#include "../AStar/MapSearchNode.h"

#include <vector>
using namespace std;

class WaypointManager
{
	vector<Cell*> m_vWaypoints;

	void LinkNextWaypoint(Cell* pNode, Cell* pLast);
	unsigned FindNextSignificantNode(vector<Cell*> vPath, unsigned dwStartNode, unsigned dwLimitNode, unsigned dwResolution, float fTestGradient, float fAccuracy);

public:
	WaypointManager(){};
	~WaypointManager();

	// Calculates a sequence of waypoints given a vector of location nodes as a path
	// vPath 	    - path as vector of nodes
	// dwResolution	    - Amount of cells to move between each path sample
	// dwLinearAccuracy - Threshold value to determine if a gradient difference between
	//			two following node pairs is significant enough to warrant a waypoint
	bool SetPath(vector<Cell*> vPath, unsigned dwResolution, float fLinearAccuracy);

	Cell* GetStartWaypoint();
	vector<Cell*> GetAllWayPoints();
};

#endif
