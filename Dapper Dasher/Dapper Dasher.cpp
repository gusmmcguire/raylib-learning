#include "raylib.h"

int main()
{
    const int windowWidth = 512;
    const int windowHeight = 380;

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //stop drawing
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
