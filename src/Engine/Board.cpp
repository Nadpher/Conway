#include "Engine.h"

int Conway::Board::CountAliveNeighbors(std::pair<int, int> GridCell)
{
    int count = 0;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j <2; ++j)
        {
            int absoluteX = GridCell.first + i;
            int absoluteY = GridCell.second + j;
            if (absoluteX == -1 || absoluteX == Engine::GRID_WIDTH ||
                absoluteY == -1 || absoluteY == Engine::GRID_HEIGHT ||
               (i == 0 && j == 0))
            {
                continue;
            }

            if (m_Grid[absoluteX + Engine::GRID_WIDTH * absoluteY] == Cell::Alive)
            {
                ++count;
            }
        }
    }
    
    return count;
}

// Inverses the cell that was clicked on
int Conway::Board::ToggleClickedCell(std::pair<int, int> Coords)
{
    SDL_Rect rect;
    
    rect.x = floor(Coords.first/m_CellSize.first)*m_CellSize.first;
    rect.y = floor(Coords.second/m_CellSize.second)*m_CellSize.second;
    rect.w = m_CellSize.first;
    rect.h = m_CellSize.second;

    int ClickedCell = (floor(Coords.first / m_CellSize.first)) + Engine::GRID_WIDTH * (floor(Coords.second / m_CellSize.second));
    m_Grid[ClickedCell] = m_Grid[ClickedCell] == Cell::Dead ? Cell::Alive : Cell::Dead;

    if (State == Cell::Alive)
    {
        SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(m_Renderer, &rect);
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    }
    else
    {
        SDL_RenderFillRect(m_Renderer, &rect);
    }

    SDL_RenderPresent(m_Renderer);
    DrawLines();
}
