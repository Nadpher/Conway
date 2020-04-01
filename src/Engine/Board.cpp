#include "Board.h"

#include <cmath>

Conway::Board::Board(Coord<int, int> ScreenSize)
    : m_CellSize{ScreenSize.first / GRID_WIDTH, ScreenSize.second / GRID_HEIGHT}
{

}

int Conway::Board::CountAliveNeighbors(std::pair<int, int> GridCell)
{
    int count = 0;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j <2; ++j)
        {
            int absoluteX = GridCell.first + i;
            int absoluteY = GridCell.second + j;
            if (absoluteX == -1 || absoluteX == GRID_WIDTH ||
                absoluteY == -1 || absoluteY == GRID_HEIGHT ||
               (i == 0 && j == 0))
            {
                continue;
            }

            if (m_Grid[absoluteX + GRID_WIDTH * absoluteY] == Cell::Alive)
            {
                ++count;
            }
        }
    }
    
    return count;
}

// Inverses the cell that was clicked on
void Conway::Board::ToggleClickedCell(std::pair<int, int> Coords)
{
    int ClickedCell = (floor(Coords.first / m_CellSize.first)) + GRID_WIDTH * (floor(Coords.second / m_CellSize.second));
    m_Grid[ClickedCell] = m_Grid[ClickedCell] == Cell::Dead ? Cell::Alive : Cell::Dead;
}

void Conway::Board::Update()
{
    std::vector<Cell> temp(m_Grid);

    for (int i = 0; i < Board::GRID_HEIGHT; ++i)
    {
        for (int j = 0; j < GRID_WIDTH; ++j)
        {
            if (m_Grid[j + GRID_WIDTH * i] == Cell::Alive)
            {
                if (CountAliveNeighbors({j, i}) < 2 || CountAliveNeighbors({j, i}) > 3)
                {
                    temp[j + GRID_WIDTH * i] = Cell::Dead;
                }
            }
            else
            {
                if (CountAliveNeighbors({j, i}) == 3)
                {
                    temp[j + GRID_WIDTH * i] = Cell::Alive;
                }
            }
        }
    }

    m_Grid = temp;
}
