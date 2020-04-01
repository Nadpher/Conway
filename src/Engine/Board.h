#include <utility>
#include <vector>

namespace Conway
{
    class Board
    {
        public:

        private:

            enum class Cell
            {
                Dead,
                Alive
            };

            int CountAliveNeighbors(std::pair<int, int> GridCell);
            void ToggleClickedCell(std::pair<int, int> MouseCoords);

            std::vector<Cell> m_Grid;
            const std::pair<int, int> m_CellSize;
    };
}
