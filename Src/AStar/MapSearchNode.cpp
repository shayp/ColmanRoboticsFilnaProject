#include "MapSearchNode.h"
#include <iostream>
#include "stlastar.h"

MapSearchNode::~MapSearchNode()
{
}
bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	char str[100];
	sprintf( str, "Node position : (%d,%d)\n", x,y );

	cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal)
{
	return fabsf(x - nodeGoal.x) + fabsf(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode>* astarsearch, MapSearchNode *parent_node, Map* map)
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards
	Cell* LeftCell = map->getCell(x - 1, y);
	if (LeftCell != NULL && LeftCell->isCellWalkable() && !(parent_x == x - 1 && parent_y == y))
	{
		NewNode = MapSearchNode(x - 1, y);
		astarsearch->AddSuccessor(NewNode);
	}

	Cell* AboveCell = map->getCell(x, y - 1);
	if (AboveCell != NULL && AboveCell->isCellWalkable() && !(parent_x == x && parent_y == y - 1))
	{
		NewNode = MapSearchNode(x, y - 1);
		astarsearch->AddSuccessor(NewNode);
	}

	Cell* rightCell = map->getCell(x + 1, y);
	if (rightCell != NULL && rightCell->isCellWalkable() && !(parent_x == x + 1 && parent_y == y))
	{
		NewNode = MapSearchNode(x + 1, y);
		astarsearch->AddSuccessor(NewNode);
	}

	Cell* bottomCell = map->getCell(x, y + 1);
	if (bottomCell != NULL && bottomCell->isCellWalkable() && !(parent_x == x && parent_y == y + 1))
	{
		NewNode = MapSearchNode(x, y + 1);
		astarsearch->AddSuccessor(NewNode);
	}

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor, Map* map)
{
	return map->getCell(x, y)->Cost;
}
