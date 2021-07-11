#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Initialization
    const int screenWidth = 1024;
    const int screenHeight = 512;

    InitWindow(screenWidth, screenHeight, "RayCaster");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
