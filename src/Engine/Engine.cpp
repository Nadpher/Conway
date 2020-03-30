#include "Engine.h"

#include <cmath>

Conway::Engine::Engine(int ScreenWidth, int ScreenHeight)
    : m_ScreenWidth{ScreenWidth}, m_ScreenHeight{ScreenHeight},
      m_CellSize{ScreenWidth / GRID_WIDTH, ScreenHeight / GRID_HEIGHT} 
{
    SDL_assert(SDL_Init(SDL_INIT_VIDEO) >= 0);

    m_Window = SDL_CreateWindow(
            "Conway's game of life",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            m_ScreenWidth,
            m_ScreenHeight,
            SDL_WINDOW_SHOWN 
            );

    SDL_assert(m_Window != NULL);

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    SDL_assert(m_Renderer != NULL);

    // In its own scope for minimum memory usage
    // Initializes the member grid
    {
        int gridsize = GRID_WIDTH * GRID_HEIGHT;
        std::vector<Cell> grid(gridsize, Cell::Dead);
        m_Grid = grid;
    }

    // Show lines
    SDL_RenderClear(m_Renderer);
    DrawLines();
}

Conway::Engine::~Engine()
{
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    m_Window = NULL;
    m_Renderer = NULL;

    SDL_Quit();
}

// Excactly what it does. Changes the cell that was clicked on
// based on the State parameter.
void Conway::Engine::ChangeClickedCell(std::pair<int, int> Coords, Cell State)
{
    SDL_Rect rect;
    
    rect.x = floor(Coords.first/m_CellSize.first)*m_CellSize.first;
    rect.y = floor(Coords.second/m_CellSize.second)*m_CellSize.second;
    rect.w = m_CellSize.first;
    rect.h = m_CellSize.second;

    int ClickedCell = Coords.first / m_CellSize.first +
        GRID_WIDTH * Coords.second / m_CellSize.second;

    m_Grid[ClickedCell] = State;

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

void Conway::Engine::DrawCells()
{

}

void Conway::Engine::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                m_Running = false;
                break;

                // Toggles the updating with a keypress
            case SDL_KEYDOWN:
                m_Update = m_Update ? false : true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    ChangeClickedCell({event.button.x, event.button.y}, Cell::Alive);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    ChangeClickedCell({event.button.x, event.button.y}, Cell::Dead);
                }
        }
    }
}

// Draws the grid
void Conway::Engine::Draw()
{
    SDL_RenderClear(m_Renderer);

    DrawLines();
    SDL_RenderPresent(m_Renderer);
}

// This function draws
// the lines delimiting each cell.
// The first loop draws the horizontal
// lines, the second one the vertical lines.
void Conway::Engine::DrawLines()
{
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    for (int i = 0; i < GRID_HEIGHT; ++i)
    {
        if (i != 0)
        {
            SDL_RenderDrawLine(
                    m_Renderer,
                    0,
                    m_CellSize.second * i,
                    m_CellSize.first * GRID_WIDTH,
                    m_CellSize.second * i
                    );
        }
    }

    for (int i = 0; i < GRID_WIDTH; ++i)
    {
        if (i != 0)
        {
            SDL_RenderDrawLine(
                    m_Renderer,
                    m_CellSize.first * i,
                    0,
                    m_CellSize.first * i,
                    m_CellSize.second * GRID_HEIGHT
                    );
        }
    }

    SDL_RenderPresent(m_Renderer);
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
} 

// Main game loop
void Conway::Engine::Run()
{
    while (m_Running)
    {
        HandleEvents();
        if (m_Update)
        {
            Update();
            Draw();
        }
    }
}

// Game logic
void Conway::Engine::Update()
{
    
}
