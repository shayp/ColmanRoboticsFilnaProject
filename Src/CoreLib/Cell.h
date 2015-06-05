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
			#define COST_OBSTICALE 		DBL_MAX
			#define COST_FREE_TO_GO 	1
			#define COST_NEAR_WALL		3
			#define NUM_OF_NEIGHBORS;

			double Cost;

			Cell(unsigned x, unsigned y, double cost = 1.0);
			Cell(const Cell& cell);
			virtual ~Cell() {}

			void setNeighbors(vector<Cell*> neighbors) { m_Neighbors = neighbors; }
			vector<Cell*> getNeighbors() { return m_Neighbors; }
			unsigned getX() { return m_loc.X; }
			unsigned getY() { return m_loc.Y; }
			CellLocation GetPos(){return m_loc;	}

			bool isCellWalkable();

		protected:
			vector<Cell*> m_Neighbors;
			CellLocation m_loc;

	};
}
