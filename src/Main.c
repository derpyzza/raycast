#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "map.h"

void MovePlayer();

//---------------------------------------player variables--------------------------------------------------

    float playerx;
    float playery;
    float playerAngle;
    float playerDeltax;
    float playerDeltay;


//------------camera---------------------
float planeX, planeY;
//------------camera---------------------

        // float rayX, rayY, rayAngle, Xoffset, Yoffset;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 512;
    playerx = 300, playery = 300;

    InitWindow(screenWidth, screenHeight, "RayCaster");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        MovePlayer();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GRAY);
        DrawMap(mapHeight, mapWidth, cellSize);
        DrawLine(playerx +5, playery, playerx + playerDeltax * 5, playery + playerDeltay * 5, YELLOW);
        // DrawLine(playerx, playery, rayX, rayY, RED);
        DrawRectangle(playerx, playery, 5, 5, YELLOW);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void MovePlayer()
{
    if (IsKeyDown(KEY_A))
    {
        playerAngle -= 0.1;
        if (playerAngle < 0)
        {
            playerAngle += 2 * PI;
        }
        playerDeltax = cos(playerAngle) * 5;
        playerDeltay = sin(playerAngle) * 5;
    }
    if (IsKeyDown(KEY_D))
    {
        playerAngle += 0.1;
        if (playerAngle > 2 * PI)
        {
            playerAngle -= 2 * PI;
        }
        playerDeltax = cos(playerAngle) * 5;
        playerDeltay = sin(playerAngle) * 5;
    }
    if (IsKeyDown(KEY_W))
    {
        playerx += playerDeltax;
        playery += playerDeltay;
    }
    if (IsKeyDown(KEY_S))
    {
        playerx -= playerDeltax;
        playery -= playerDeltay;
    }
}


void drawRay()
{
    // int r, dof, mapX, mapY, mapPosition;

    // rayAngle = playerAngle;

    // for (r = 0; r < 1; r++){
    //     dof = 0;
    //     float aTan = -1 / tan(rayAngle);

        
    // }
}

