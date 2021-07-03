#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "map.h"

void MovePlayer();

float playerx;
float playery;
float playerSpeed = 5;
float playerAngle;
float rayY, rayX, yOffset, xOffset;

int main(void)
{
    // Initialization
    const int screenWidth = 512;
    const int screenHeight = 512;
    playerx = 300, playery = 300;

    InitWindow(screenWidth, screenHeight, "RayCaster");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // TODO: Update your variables here
        MovePlayer();

        // Draw
        BeginDrawing();

        ClearBackground(GRAY);
        DrawMap(mapHeight, mapWidth, cellSize);
        DrawRectangle(playerx, playery, 5, 5, YELLOW);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void MovePlayer()
{
    if (IsKeyDown(KEY_W))
    {
        playery -= playerSpeed;
    }
    if (IsKeyDown(KEY_S))
    {
        playery += playerSpeed;
    }
    if (IsKeyDown(KEY_A))
    {
        playerx -= playerSpeed;
    }
    if (IsKeyDown(KEY_D))
    {
        playerx += playerSpeed;
    }
}
