#include "Engine.h"

Conway::Engine::Engine(int ScreenWidth, int ScreenHeight)
    : m_ScreenWidth{ScreenWidth}, m_ScreenHeight{ScreenHeight}
{
    m_Window = SDL_CreateWindow(
            "Conway's game of life",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            m_ScreenWidth,
            m_ScreenHeight,
            SDL_WINDOW_SHOWN 
            );

    static_assert(*m_Window != NULL, "Could not initialize window.\n");
}

Conway::Engine::~Engine()
{
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    m_Window = NULL;
    m_Renderer = NULL;

    SDL_Quit();
}
