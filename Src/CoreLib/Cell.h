#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include "Location.h"
#include <float.h>

using namespace std;

namespace CoreLib
{

	class Cell
	{
		public:
			#define COST_OBSTICALE 			DBL_MAX
			#define COST_FREE_TO_GO 		0
			#define COST_SECOND_LEVEL 		4
			#define COST_NEAR_WALL			7
			#define COST_NEAR_WALL_SECOND	6
			#define COST_NEAR_WALL_THIRD	5
			#define NUM_OF_NEIGHBORS	8

			double Cost;
			CellLocation m_loc;
			Cell(unsigned x, unsigned y, double cost = 1.0);
			Cell(const Cell& cell);
			virtual ~Cell() {}

			void setNeighbors(vector<Cell*> neighbors) { m_Neighbors = neighbors; }
			vector<Cell*> getNeighbors() { return m_Neighbors; }
			unsigned getX() { return m_loc.X; }
			unsigned getY() { return m_loc.Y; }
			bool IsWayPoint();
			void SetAsWayPoint();
			CellLocation GetPos(){return m_loc;	}

			bool isCellWalkable();

		protected:
			vector<Cell*> m_Neighbors;
			bool m_fIsWayPoint;

	};
}
#endif
