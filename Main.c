#include "raylib.h"
#include <stdio.h>
#include <math.h>

void MovePlayer();
void DrawMap(int width, int height, int size);

//---------------------------------------player variables--------------------------------------------------

float playerx;
float playery;
float playerAngle;
float playerDeltax;
float playerDeltay;
float dirX = -1, dirY = 0;
//-- FOV = 60;

//------------camera---------------------
float planeX, planeY;
//------------camera---------------------

//---------------------------------------player variables--------------------------------------------------

//---------------------------------------ray variables----------------------------------------------------

        float rayX, rayY, rayAngle, Xoffset, Yoffset;

//---------------------------------------ray variables----------------------------------------------------

//--------------------------------------map variables-----------------------------------------------------
int cc = 1;
int mapHeight = 16;
int mapWidth = 16;
int cellSize = 32;
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

        rayAngle = playerAngle;

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
        printf("%f RAY: \n", rayAngle);
        printf("%f PLAYER: \n", playerAngle);
        MovePlayer();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GRAY);
        DrawMap(mapHeight, mapWidth, cellSize);
        DrawLine(playerx +5, playery, playerx + playerDeltax * 5, playery + playerDeltay * 5, YELLOW);
        DrawLine(playerx, playery, rayX, rayY, RED);
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
    int r, dof, mapX, mapY, mapPosition;

    for (r = 0; r < 1; r++){
        dof = 0;
        float aTan = -1 / tan(rayAngle);

        //if ray's looking down
        if (rayAngle < PI){
            rayY = (((int) playery >> 5) << 5) -0.0001;
            rayX = (playery - rayY) * aTan + playerx;
            Yoffset = -cellSize;
            Xoffset = -Yoffset * aTan;
        }
        //if ray's looking up
        if (rayAngle > PI){
            rayY = (((int) playery >> 5) << 5) + 64;
            rayX = (playery - rayY) * aTan + playerx;
            Yoffset = cellSize;
            Xoffset = -Yoffset * aTan;
        }
        if (rayAngle == 0 || rayAngle == PI){
            rayX = playerx;
            rayY = playery;
            dof = 8;
        }
        while (dof < 8){
            mapX = (int) (rayX) >> 5;
            mapY = (int) (rayY) >> 5;
            mapPosition = mapY * mapWidth + mapX;

            if(mapPosition < mapWidth * mapHeight && map[mapPosition][mapPosition] == 1){
                dof = 8;
            }else{
                rayX += Xoffset;
                rayY += Yoffset;
                dof += 1;
            }
        }
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
