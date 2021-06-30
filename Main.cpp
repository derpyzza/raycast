#include "include/raylib.h"
#include <math.h>

void MovePlayer(void);
void DrawMap(int width, int height, int size);

float px, py, pa, pdx, pdy;
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
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 512;
    px = 300, py = 300;

    InitWindow(screenWidth, screenHeight, "RayCaster");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // DrawMap(mapx, mapy);

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
        DrawLine(px + 5, py, px + pdx * 5, py + pdy * 5, RED);
        DrawRectangle(px, py, 5, 5, YELLOW);

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
        pa -= 0.1;
        if (pa < 0)
        {
            pa += 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if (IsKeyDown(KEY_D))
    {
        pa += 0.1;
        if (pa > 2 * PI)
        {
            pa -= 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if (IsKeyDown(KEY_W))
    {
        px += pdx;
        py += pdy;
    }
    if (IsKeyDown(KEY_S))
    {
        px -= pdx;
        py -= pdy;
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
