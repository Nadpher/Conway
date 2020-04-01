#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Board.h"

// Namespace Conway to
// always enclose classes in a namespace.
namespace Conway
{
    // The engine class handles
    // everything about the program:
    // It handles the window, the renderer,
    // Drawing, Events, Game logic,
    // and holds representations of the game's
    // parts (Cell, Grid)
    class Engine
    {
        public:
            Engine(int ScreenWidth, int ScreenHeight);
            ~Engine(); 

            void Run();

        private:

            void HandleEvents();
            void Draw();

            void DrawLines();

            const int m_ScreenWidth;
            const int m_ScreenHeight;

            bool m_Update = false;
            bool m_Running = true;

            std::unique_ptr<Board> m_Board;

            SDL_Window* m_Window;
            SDL_Renderer* m_Renderer;
    };
}
