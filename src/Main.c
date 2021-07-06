#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "map.h"

void MovePlayer();
void CastRay();
float Vec2Rad(Vector2 v);

float playerx;
float playery;
float playerSpeed;
float direction;
int FOV;

float nhx, nhy, hxo, hyo;

typedef struct ray
{
    float rayx;
    float rayy;
    Vector2 Dir;
} ray;

ray Test;

int main(void)
{
    // Initialization
    const int screenWidth = 1024;
    const int screenHeight = 512;
    playerx = 300;
    playery = 300;
    direction = 0;
    playerSpeed = 5;
    ray Test = {playerx, playery, {1, 1}};

    InitWindow(screenWidth, screenHeight, "RayCaster");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // TODO: Update your variables here
        // CastRay();
        MovePlayer();
        
        float ra = Vec2Rad(Test.Dir);
        printf("X: %f, Y: %f, Angle: %f \n", Test.Dir.x, Test.Dir.y, ra);

        // Draw
        BeginDrawing();

        ClearBackground(GRAY);
        // DrawMap(mapHeight, mapWidth, cellSize);
        DrawRectangle(playerx, playery, 5, 5, YELLOW);
        DrawLine(playerx, playery, playerx + (Test.Dir.x * 10), playery + (Test.Dir.y * 10), RED);
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

// void CastRay()
// {
//     int dof;
//     Vec2Rad(Test.Dir);
//     int mx, my, mp;
//     //horizontal line variables
//     float RayX, RayY, nextX, nextY;
    
//     printf("%f RAY:\n", Test.Dir);

// }

float Vec2Rad(Vector2 v)
{
    float angle = atan2(v.y, v.x);
    return angle;
}