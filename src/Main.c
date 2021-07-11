#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "map.h"

//Prototypes;
void MovePlayer();
void DrawRay2D(Ray r, float rx, float ry);
void CastRay();
float Vec2Rad(Vector2 v);

float playerx;
float playery;
float playerSpeed;
float direction;
int FOV;

typedef struct ray
{
    float rayx;
    float rayy;
    Vector2 Dir;
} ray;

int main(void)
{
    // Initialization
    const int screenWidth = 1024;
    const int screenHeight = 512;
    playerx = 300;
    playery = 300;
    direction = 0;
    playerSpeed = 5;

    InitWindow(screenWidth, screenHeight, "RayCaster");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        MovePlayer();

        BeginDrawing();

        ClearBackground(GRAY);
        DrawMap(mapHeight, mapWidth, cellSize);
        DrawRectangle(playerx, playery, 5, 5, YELLOW);
        CastRay();

        EndDrawing();
    }
    CloseWindow();

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

void DrawRay2D(ray r, float rx, float ry)
{
    DrawLine(playerx, playery, rx, ry, RED);
}

void CastRay()
{
    ray Test = {
        .rayx = playerx,
        .rayy = playery,
        .Dir = {-1, 1}
    };
    float ra = Vec2Rad(Test.Dir);
    int dof, mx, my, mp;
    float RayX, RayY, nextX, nextY;

    //if the ray is looking up;
    if (ra > PI)
    {
        RayY = (playery / cellSize) * (cellSize)-1;
        RayX = playerx + (playery - RayY) / tan(ra);
        nextY = -cellSize;
        nextX = -cellSize / tan(ra);
    }
     if (ra < PI)
    {
        RayY = (playery / cellSize) * (cellSize) + 64;
        RayX = playerx + (playery - RayY) / tan(ra);
        nextY = cellSize;
        nextX = -cellSize / tan(ra);
    }
    if (ra == 0 || ra == PI){
        RayX = playerx; RayY = playery;
        dof = 8;
    }

    while (dof < 8)
    {
        mx = (int) RayX / 64;
        my = (int) RayY / 64;
        mp = my * mapWidth + mx;
        if(map[mp] == 1){
            printf("hit");
        }
    }
    DrawRay2D(Test, RayX, RayY);
}

float Vec2Rad(Vector2 v)
{
    float angle = atan2(v.y, v.x);
    return angle;
}