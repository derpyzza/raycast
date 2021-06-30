#include "raylib.h"
#include <stdio.h>
#include <math.h>

void MovePlayer(void);
void DrawMap(int width, int height, int size);

//---------------------------------------player variables--------------------------------------------------

float playerx;
float playery;
float playerAngle;
float playerDeltax;
float playerDeltay;
float dirX = -1, dirY = 0;

    //------------camera---------------------
    float camX, camY;
    //------------camera---------------------

//---------------------------------------player variables--------------------------------------------------


//--------------------------------------map variables-----------------------------------------------------
int cc = 1;
int mapx = 16;
int mapy = 16;
int mapsize = 32;
int map[16][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

//--------------------------------------map variables-----------------------------------------------------



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

        if (IsKeyPressed(KEY_T))
        {
            cc = 1;
        }
        else if (IsKeyPressed(KEY_Y))
        {
            cc = 0;
        }
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        MovePlayer();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GRAY);
        DrawMap(mapx, mapy, mapsize);
        DrawLine(playerx +5, playery, playerx + playerDeltax * 5, playery + playerDeltay * 5, RED);
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
void MovePlayer(void)
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

//map draw function
void DrawMap(int width, int height, int size)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y][x] == 1)
            {
                DrawRectangle(x * size, y * size, size - cc, size - cc, GREEN);
            }
            else if (map[y][x] == 0)
            {
                DrawRectangle(x * size, y * size, size - cc, size - cc, BLACK);
            }
        }
    }
}
