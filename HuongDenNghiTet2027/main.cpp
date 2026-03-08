#include "raylib.h"
#include "HashTable.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Double Hashing Visualizer");
    SetTargetFPS(60);
    
    doubleHash myHash(23);
    myHash.insert(10);
    myHash.insert(33);
    myHash.insert(56);
    myHash.insert(15);
    myHash.insert(20);
    myHash.insert(43);
    myHash.erase(33);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Double Hashing Hash Map", 20, 20, 24, DARKGRAY);
        DrawText("Green: Occupied | White (E): Empty (-1) | Red (D): Deleted (-2)", 20, 50, 16, GRAY);
        myHash.draw(screenWidth, screenHeight);
        EndDrawing();
    }
    CloseWindow();
}