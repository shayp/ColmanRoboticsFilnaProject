#include "Map.h"

using namespace std;
using namespace CoreLib;

Map::Map(unsigned rows, unsigned cols)
{
	init(rows, cols);
}

void Map::init(unsigned rows, unsigned cols)
{
	m_Rows = rows;
	m_Cols = cols;

	m_Cells.resize(rows);
	for (unsigned i = 0; i < rows; i++)
	{
		m_Cells[i].resize(cols);
		for (unsigned j = 0; j < cols; j++)
		{
			// Initialize cells
			m_Cells[i][j] = new Cell(i, j);
		}
	}
	attachNeighbors();
}

void Map::attachNeighbors()
{
	for (unsigned i = 0; i < m_Rows; i++)
	{
		for (unsigned j = 0; j < m_Cols; j++)
		{
			vector<Cell*> nbrs;
			nbrs.resize(NUM_OF_NEIGHBORS);
			// Top
			if (i != 0)
			{
				if (j != 0)
				{
					// Top left
					nbrs[0] = m_Cells[i - 1][j - 1];
				}
				// Top middle
				nbrs[1] = m_Cells[i - 1][j];
				if (j < m_Cols - 1)
				{
					// Top right
					nbrs[2] = m_Cells[i - 1][j + 1];
				}
			}
			if (j < m_Cols - 1)
			{
				// Middle right
				nbrs[3] = m_Cells[i][j + 1];
			}
			// Bottom
			if (i < m_Rows - 1)
			{
				if (j < m_Cols - 1)
				{
					// Bottom right
					nbrs[4] = m_Cells[i + 1][j + 1];
				}
				// Bottom middle
				nbrs[5] = m_Cells[i + 1][j];
				if (j != 0)
				{
					// Bottom left
					nbrs[6] = m_Cells[i + 1][j - 1];
				}
			}
			if (j != 0)
			{
				// Middle left
				nbrs[7] = m_Cells[i][j - 1];
			}
			m_Cells[i][j]->setNeighbors(nbrs);
		}
	}
}

Map::Map(const Map& map) : m_Rows(map.m_Rows), m_Cols(map.m_Cols) {
	init(map.m_Rows, map.m_Cols);

	for (unsigned row = 0; row < map.m_Rows; row++)
	{
		for (unsigned col = 0; col < map.m_Cols; col++)
		{
			Cell* cell = map(row, col);
			m_Cells[row][col] = new Cell(*cell);
		}
	}
}

Map::~Map()
{
	freeMem();
}

void Map::freeMem()
{
	for (unsigned row = 0; row < m_Rows; row++)
	{
		for (unsigned col = 0; col < m_Cols; col++)
		{
			delete m_Cells[row][col];
			m_Cells[row][col] = NULL;
		}

		m_Cells[row].clear();
	}
	m_Cells.clear();
}

Cell* Map::operator()(const int row, const int col) const
{
	return getCell(row, col);
}

Cell* Map::getCell(int row, int col) const
{
	if (!isInRange(row, col))
	{
		return NULL;
	}

	return m_Cells[row][col];
}

bool Map::isInRange(int row, int col) const
{
	return ((row >= 0 && row < (int)m_Rows) &&
			(col >= 0 && col < (int)m_Cols));
}


