#include "Cell.h"

using namespace CoreLib;

Cell::Cell(unsigned x, unsigned y, double cost)
{
	m_loc.X = x;
	m_loc.Y = y;
	Cost = cost;
	m_wayPointType = eNotWayPoint;
}

Cell::Cell(const Cell& cell)
{
	m_Neighbors = cell.m_Neighbors;
	m_loc = cell.m_loc;
	Cost = cell.Cost;
	m_wayPointType = eNotWayPoint;
}


bool Cell::isCellWalkable()
{
	return (Cost != COST_OBSTICALE);
}

unsigned Cell::GetWayPointType()
{
	return m_wayPointType;
}
void Cell::SetAsWayPoint(unsigned wayPointType)
{
	m_wayPointType = wayPointType;
}
