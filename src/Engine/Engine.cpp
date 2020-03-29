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

    SDL_assert(m_Window != NULL);

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    SDL_assert(m_Renderer != NULL);
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
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                m_Running = false;
                break;
        }
    }
}

void Conway::Engine::Draw()
{
    SDL_RenderClear(m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

void Conway::Engine::Run()
{
    while (m_Running)
    {
        HandleEvents();
        Update();
        Draw();
    }
}

void Conway::Engine::Update()
{
    
}
