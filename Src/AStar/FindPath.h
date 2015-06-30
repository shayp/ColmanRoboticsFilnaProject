#ifndef FIND_PATH_H
#define FIND_PATH_H
#include "../CoreLib/Map.h"
#include "MapSearchNode.h"
#include "stlastar.h"
#include <vector>

using namespace CoreLib;

class FindPath
{
public:
	FindPath(Map* map);
	~FindPath();

	vector<Cell*> search(Cell* startCell, Cell* endCell);

private:
	Map* m_Map;
	AStarSearch<MapSearchNode> m_AStarSearch;
	vector<MapSearchNode*> GetSolution();
	Cell* WayPointnodeToCell(MapSearchNode* node);

};
#endif
