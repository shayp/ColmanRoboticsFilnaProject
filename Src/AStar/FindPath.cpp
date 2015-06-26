#include "FindPath.h"
#include "MapSearchNode.h"
#include <vector>
FindPath::FindPath(Map* map) : m_Map(map)
{
}

vector<Cell*> FindPath::search(Cell* startCell, Cell* endCell)
{
	MapSearchNode startNode = new MapSearchNode();
	startNode.x = startCell->getX();
	startNode.y = startCell->getY();

	MapSearchNode endNode = new MapSearchNode();
	endNode.x = endCell->getX();
	endNode.y = endCell->getY();

	m_AStarSearch.SetStartAndGoalStates(startNode, endNode);

	unsigned searchState;

	// Search
	do {
		searchState = m_AStarSearch.SearchStep(m_Map);

	} while (searchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

}
