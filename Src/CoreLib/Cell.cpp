#include "Cell.h"

using namespace CoreLib;

Cell::Cell(unsigned x, unsigned y, double cost)
{
	m_loc.X = x;
	m_loc.Y = y;
	Cost = cost;
	m_fIsWayPoint = false;
}

Cell::Cell(const Cell& cell)
{
	m_Neighbors = cell.m_Neighbors;
	m_loc = cell.m_loc;
	Cost = cell.Cost;
	m_fIsWayPoint = false;
}


bool Cell::isCellWalkable()
{
	return (Cost != COST_OBSTICALE);
}

bool Cell::IsWayPoint()
{
	return m_fIsWayPoint;
}
void Cell::SetAsWayPoint()
{
	m_fIsWayPoint = true;
}
