#include "Engine.h"

Conway::Engine::Engine(int ScreenWidth, int ScreenHeight)
    : m_ScreenWidth{ScreenWidth}, m_ScreenHeight{ScreenHeight}
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

    if (!m_Board->
    {
        m_Board->= std::make_unique<Board>(m_ScreenWidth, m_ScreenHeight);
    }

    SDL_assert(m_Window != NULL);

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_assert(m_Renderer != NULL);

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

void Conway::Engine::HandleEvents()
{
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_QUIT:
                m_Running = false;
                break;

                // Toggles the updating with a keypress
            case SDL_KEYDOWN:
                if (Event.key.keysym.sym == SDLK_SPACE)
                {
                    m_Update = m_Update ? false : true;
                    DrawLines();
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (!m_Update)
                {
                    if (Event.button.button == SDL_BUTTON_LEFT)
                    {
                        m_Board->ToggleClickedCell({Event.button.x, Event.button.y});
                    }
                }
                break;

        }
    }
}

// Draws the grid
void Conway::Engine::Draw()
{
    SDL_RenderClear(m_Renderer);

    for (int i = 0; i < Board::Board::GRID_HEIGHT; ++i)
    {
        for (int j = 0; j < Board::GRID_WIDTH; ++j)
        {
            if (m_Board->ReadCell(j + Board::GRID_WIDTH * i) == Cell::Alive)
            {
                SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
            }
            else 
            {
                SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
            }

            SDL_Rect rect;
            rect.x = m_Board->GetCellSize().first * j;
            rect.y = m_Board->GetCellSize().second * i;
            rect.w = m_Board->GetCellSize().first;
            rect.h = m_Board->GetCellSize().second;

            SDL_RenderFillRect(m_Renderer, &rect);
            }
    }
    if (!m_Update)
    {
        DrawLines();
    }

    SDL_RenderPresent(m_Renderer);
}

// This function draws
// the lines delimiting each cell.
// The first loop draws the horizontal
// lines, the second one the vertical lines.
void Conway::Engine::DrawLines()
{
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    for (int i = 0; i < Board::GRID_HEIGHT; ++i)
    {
        if (i != 0)
        {
            SDL_RenderDrawLine(
                    m_Renderer,
                    0,
                    m_Board->GetCellSize().second * i,
                    m_Board->GetCellSize().first * Board::GRID_WIDTH,
                    m_Board->GetCellSize().second * i
                    );
        }
    }

    for (int i = 0; i < Board::GRID_WIDTH; ++i)
    {
        if (i != 0)
        {
            SDL_RenderDrawLine(
                    m_Renderer,
                    m_Board->GetCellSize().first * i,
                    0,
                    m_Board->GetCellSize().first * i,
                    m_Board->GetCellSize().second * Board::GRID_HEIGHT
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
            m_Board->Update();
        }
        Draw();

        SDL_Delay(100);
    }
}
