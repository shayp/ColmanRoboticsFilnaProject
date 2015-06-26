#ifndef MAP_SEARCH_NODE_H
#define MAP_SEARCH_NODE_H

#include "stlastar.h"
#include "../CoreLib/Map.h"

using namespace std;
using namespace CoreLib;

class MapSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;

	MapSearchNode() { x = y = 0; }
	MapSearchNode( int px, int py ) { x=px; y=py; }
	~MapSearchNode();
	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node, Map* map);
	float GetCost( MapSearchNode &successor, Map* map);
	bool IsSameState( MapSearchNode &rhs );

	void PrintNodeInfo();


};

#endif
