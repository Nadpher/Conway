#include <vector>

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

            void run();

        private:

            void HandleInput();
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
    };
}
