#include <vector>
#include <SDL2/SDL.h>
#include <utility>

// Grid must always have same size,
// so i define them with preprocessor
// because there is no need for a varible.
#define GRID_WIDTH 80
#define GRID_HEIGHT 60

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
            void Update();

            enum class Cell
            {
                Dead,
                Alive
            };
            std::vector<Cell> m_Grid;
            const int m_ScreenWidth;
            const int m_ScreenHeight;
            const std::pair<int, int> m_CellSize;
            bool m_Running = true;

            SDL_Window* m_Window;
            SDL_Renderer* m_Renderer;
    };
}
