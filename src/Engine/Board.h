#pragma once

#include <vector>

#include "Coord.h"

namespace Conway
{
    class Board
    {
        public:
            Board(Coord<int, int> ScreenSize);
            
            static constexpr int GRID_WIDTH = 80;
            static constexpr int GRID_HEIGHT = 60;

            Coord<int, int> GetCellSize() { return m_CellSize; }
            void ToggleClickedCell(Coord<int, int> MouseCoords);
            void Update();
            void Clear();

            enum class Cell
            {
                Dead,
                Alive
            };

        private:

            int CountAliveNeighbors(Coord<int, int> GridCell);

            std::vector<Cell> m_Grid;
            const Coord<int, int> m_CellSize;

        public:
            Cell ReadCell(int Index) { return m_Grid[Index]; }
    };
}
