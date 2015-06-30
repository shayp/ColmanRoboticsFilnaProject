#include "FindPath.h"
#include "MapSearchNode.h"
#include <vector>
FindPath::FindPath(Map* map) : m_Map(map)
{
}

vector<Cell*> FindPath::search(Cell* startCell, Cell* endCell)
{
	MapSearchNode startNode;
	startNode.x = startCell->getX();
	startNode.y = startCell->getY();

	cout << "A* start:" << startNode.x << "," << startNode.y << endl;
	MapSearchNode endNode;
	endNode.x = endCell->getX();
	endNode.y = endCell->getY();

	cout << "A* end:" << endNode.x << "," << endNode.y << endl;

	m_AStarSearch.SetStartAndGoalStates(startNode, endNode);
	cout << "SetStartAndGoalStates Done" << endl;
	unsigned searchState;

	// Find path
	do
	{
		searchState = m_AStarSearch.SearchStep(m_Map);

	} while (searchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

	// If searched finished
	if (searchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED)
	{
			vector<MapSearchNode*> solutionNodes = GetSolution();
			vector<Cell*> solutionCells;

			cout << "Num of waypoints " << solutionNodes.size() << endl;

			for (MapSearchNode* node : solutionNodes)
			{
				solutionCells.push_back(WayPointnodeToCell(node));
			}

			m_AStarSearch.FreeSolutionNodes();

			return solutionCells;
		}
		else if (searchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED)
		{
			cout << "Error finding A* waypoints" << endl;
		}

	return vector<Cell*>();
}

vector<MapSearchNode*> FindPath::GetSolution()
{
	vector<MapSearchNode*> solution = vector<MapSearchNode*>();

	MapSearchNode* currentNode = m_AStarSearch.GetSolutionStart();
	while (currentNode != NULL)
	{
		solution.push_back(currentNode);
		currentNode = m_AStarSearch.GetSolutionNext();
	}

	return solution;
}

Cell* FindPath::WayPointnodeToCell(MapSearchNode* node)
{
	m_Map->getCell(node->x, node->y)->SetAsWayPoint();
	return m_Map->getCell(node->x, node->y);
}
