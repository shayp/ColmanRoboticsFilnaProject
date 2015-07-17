#include "WayPointManager.h"
#include "../CoreLib/Cell.h"
#include "../Utils/PositionUtils.h"
#include <cmath>

using namespace CoreLib;
using namespace Utils;

WaypointManager::~WaypointManager()
{
	for (unsigned i = 0; i < m_vWaypoints.size(); i++)
	{
		delete m_vWaypoints[i];
	}
}

unsigned WaypointManager::FindNextSignificantNode(vector<Cell*> vPath, unsigned dwStartNode, unsigned dwLimitNode, unsigned dwResolution, float fTestGradient, float fAccuracy)
{
	Cell* pTestNode = vPath[dwStartNode];
	unsigned dwCurrNode;
	float fCurrentGradient;

	// Begin traversing path nodes according to sample resolution
	for (dwCurrNode = dwStartNode + dwResolution; dwCurrNode < vPath.size() && dwCurrNode < dwLimitNode; dwCurrNode += dwResolution)
	{

		Location from, to;

		from.setX(pTestNode->getX());
		from.setY(pTestNode->getY());
		to.setX(vPath[dwCurrNode]->getX());
		to.setY(vPath[dwCurrNode]->getY());
		// Calculate current gradient
		fCurrentGradient = PositionUtils::CalcGradient(from, to);

		/*printf("Comparing nodes %u (%u, %u) and %u (%u, %u), is gradient %f significant enough next to %f? ",
			dwStartNode, pTestNode->GetXPos(), pTestNode->GetYPos(),
			dwCurrNode, vPath[dwCurrNode]->GetXPos(), vPath[dwCurrNode]->GetYPos(),
			fCurrentGradient, fTestGradient);*/

		// If gradient of line between last node and current changed enough
		if (fCurrentGradient != fTestGradient && abs(fCurrentGradient - fTestGradient) >= fAccuracy)
		{
		//	printf("yes\n");
			break;
		}

		//printf("no\n");
	}

	//printf("Next sig node from %u is %u\n", dwStartNode, dwCurrNode);

	return dwCurrNode;
}

void WaypointManager::LinkNextWaypoint(Cell* pNode, Cell* pLast)
{
	m_vWaypoints.push_back(pNode);

}

bool WaypointManager::SetPath(vector<Cell*> vPath, unsigned dwResolution, float fLinearAccuracy)
{
	if (1 >= vPath.size() || 0 == dwResolution || 0 == fLinearAccuracy)
		return false;

	unsigned dwCurrNode = 0;
	Cell *pNewWaypoint, *pLastWaypoint;
	float fLastGradient = 0, fCurrentGradient = 0, fCurrentSubGradient = 0;

	// Starting node is always a new waypoint...
	LinkNextWaypoint(vPath[0], NULL);

	Location from;
	Location to;

	from.setX(vPath[0]->getX());
	from.setY(vPath[0]->getY());

	to.setX(vPath[1]->getX());
	to.setY(vPath[1]->getY());

	// Initial lookup values
	fLastGradient = PositionUtils::CalcGradient(from, to);

	// Begin searching for significant waypoints
	for (unsigned dwLastNode = 1, dwCurrNode = FindNextSignificantNode(vPath, 0, vPath.size(), dwResolution, fLastGradient, fLinearAccuracy);
		   dwCurrNode < vPath.size();
		   dwCurrNode = FindNextSignificantNode(vPath, dwCurrNode, vPath.size(), dwResolution, fLastGradient, fLinearAccuracy))
	{
		Location from;
		Location to;
		from.setX(vPath[dwCurrNode - dwResolution]->m_loc.X);
		from.setY(vPath[dwCurrNode - dwResolution]->m_loc.Y);
		to.setX(vPath[dwCurrNode]->m_loc.X);
		to.setY(vPath[dwCurrNode]->m_loc.Y);
		fCurrentGradient = PositionUtils::CalcGradient(from, to);

		// Found a node where there's a difference, mark as waypoint
		LinkNextWaypoint(vPath[dwCurrNode], pLastWaypoint);

		//printf("Setting new test gradient as that between %u and %u (%f)\n", dwCurrNode - dwResolution, dwCurrNode, fCurrentGradient);

		dwLastNode = dwCurrNode;
		fLastGradient = fCurrentGradient;

	}

	// Set the last node as a waypoint too, of course
	LinkNextWaypoint(vPath[vPath.size()-1], pLastWaypoint);

	return true;
}

Cell* WaypointManager::GetStartWaypoint()
{
	Cell* pStart = NULL;

	if (0 != m_vWaypoints.size())
	{
		pStart = m_vWaypoints[0];
	}

	return pStart;
}

vector<Cell*> WaypointManager::GetAllWayPoints()
{
	return m_vWaypoints;
}

