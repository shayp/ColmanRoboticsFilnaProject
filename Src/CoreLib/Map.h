#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Cell.h"

using namespace std;
namespace CoreLib
{
	class Map
	{
		public:
			Map(unsigned rows, unsigned cols);
			Map(const Map& map);
			virtual ~Map();

			unsigned getCols() const
			{
				return m_Cols;
			}
			unsigned getRows() const
			{
				return m_Rows;
			}

			bool isInRange(int row, int col) const;
			Cell* getCell(int row, int col) const;

			Cell* operator()(int row, int col) const;
			void printMap();
		protected:
			unsigned m_Rows;
			unsigned m_Cols;
			vector<vector<Cell*> > m_Cells;

		private:
			void freeMem();
			void init(unsigned rows, unsigned cols);
			void attachNeighbors();
	};
}

#endif
