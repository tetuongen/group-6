#include <raylib.h> 
#include "dijkstra.h"

int main()
{
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Dijkstra visualization");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            
        EndDrawing();
    }
    
    CloseWindow();
}