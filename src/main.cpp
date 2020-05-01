#include "Engine/Engine.h"

int main(int argc, char* argv[])
{
    Conway::Engine Engine(1280, 1024);
    Engine.Run();

    return 0;
}
