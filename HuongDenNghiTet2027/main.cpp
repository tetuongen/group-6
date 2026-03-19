#include "raylib.h"
#include "HashTable.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Double Hashing Visualizer");
    SetTargetFPS(60);

    doubleHash myHash(23);

    myHash.insert(10, false);
    myHash.insert(33, false);
    myHash.insert(56, false);
    myHash.insert(15, false);
    myHash.insert(20, false);
    myHash.insert(43, false);
    myHash.erase(33);

    Button addButton(200, 400, 150, 50, "Add", SKYBLUE);
    Button removeButton(360, 400, 150, 50, "Remove", SKYBLUE);
    Button searchButton(520, 400, 150, 50, "Search", SKYBLUE);
    InputBox numberInput(50, 402, 125, 46);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        myHash.updateAnimation(deltaTime);

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        numberInput.checkPressed(mousePosition, mousePressed);
        numberInput.Update();

        if (addButton.isPressed(mousePosition, mousePressed)) {
            int valueToInsert = numberInput.GetValue();
            if (valueToInsert != -1) {
                myHash.insert(valueToInsert); 
                numberInput.Clear();
            }
        }

        if (removeButton.isPressed(mousePosition, mousePressed)) {
            int valueToInsert = numberInput.GetValue();
            if (valueToInsert != -1) {
                myHash.erase(valueToInsert);
                numberInput.Clear();
            }
        }

        if (searchButton.isPressed(mousePosition, mousePressed)) {
            int valueToInsert = numberInput.GetValue();
            if (valueToInsert != -1) {
                myHash.search(valueToInsert);
                numberInput.Clear();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Double Hashing Hash Map", 20, 25, 32, DARKGRAY);
        DrawText("Green: Occupied | White (E): Empty (-1) | Red (D): Deleted (-2)", 20, 60, 20, GRAY);
        numberInput.Draw();
        addButton.draw(); removeButton.draw(); searchButton.draw(); 
        myHash.draw(screenWidth, screenHeight);
        EndDrawing();
    }
    CloseWindow();
}