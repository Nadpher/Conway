#pragma once

#include <vector>

#include "Coord.h"

namespace Conway
{
    class Board
    {
        public:
            
            static constexpr int GRID_WIDTH = 80;
            static constexpr int GRID_HEIGHT = 60;

            Coord<int, int> GetCellSize() { return m_CellSize; }

        private:

            enum class Cell
            {
                Dead,
                Alive
            };

            int CountAliveNeighbors(Coord<int, int> GridCell);
            void ToggleClickedCell(Coord<int, int> MouseCoords);

            std::vector<Cell> m_Grid;
            const Coord<int, int> m_CellSize;
    };
}
