#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "map.h"

void MovePlayer();

float playerx;
float playery;
float playerSpeed;
float direction;

struct Ray
{
    int a;
};
struct Ray things[10];

int main(void)
{
    // Initialization
    const int screenWidth = 512;
    const int screenHeight = 512;
    playerx = 300, playery = 300;
    direction = 0;
    playerSpeed = 5;

    InitWindow(screenWidth, screenHeight, "RayCaster");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // TODO: Update your variables here
        MovePlayer();

        for (int i = 0; i < 10; i++)
        {
            /* code */
            things[i].a = i;
            printf("%i \n", things[i].a);
        }
        

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
