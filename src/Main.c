#include "raylib.h"
#include <stdio.h>
#include <math.h>
#define P2 PI / 2
#define P3 3 * PI / 2

void DrawMap();
void MovePlayer();
void DrawPlayer();
void CastRay();

float deg2rad(float degree)
{
    return degree * PI / 180;
}

//ANCHOR distance calculation
float dist(float x1, float y1, float x2, float y2, float ang)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float px, py, pa, pdx, pdy, pdir = 0;
int cellSize = 64, mapWidth = 8, mapHeight = 8;
int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1};



int main(void)
{
    // Initialization
    const int screenWidth = 1024;
    const int screenHeight = 512;
    px = 300, py = 300;
    pdx = cos(pa) * 5, pdy = sin(pa) * 5;

    InitWindow(screenWidth, screenHeight, "RayCaster");
    SetTargetFPS(120);

    // Main game loop
    while (!WindowShouldClose())
    {
        MovePlayer();

        BeginDrawing();
            ClearBackground(GRAY);
            DrawMap();
            Color c;
            if(GetFPS() < 60){
                c = RED;
            }else if(GetFPS() == 60){
                c = YELLOW;
            }else{
                c = GREEN;
            }
            DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, c);
            DrawPlayer();
            CastRay();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void DrawPlayer()
{
    DrawRectangle(px, py, 5, 5, YELLOW);
    DrawLine(px, py, px + pdx * 5, py + pdy * 5, RED);
}

void MovePlayer()
{

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
    if (IsKeyDown(KEY_A))
    {
        pa -= deg2rad(2);
        if (pa < 0)
        {
            pa += 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if (IsKeyDown(KEY_D))
    {
        pa += deg2rad(2);
        if (pa > 2 * PI)
        {
            pa -= 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
}

void CastRay()
{
    float rx = 0, ry = 0, xo = 0, yo = 0, ra, distT = 0;
    int dof, mx, my, mp = 0;
    float DR = deg2rad(1);

    ra = pa - DR * 30;
    if (ra < 0)
    {
        ra += 2 * PI;
    }
    if (ra > 2 * PI)
    {
        ra -= 2 * PI;
    }

    for (int r = 0; r < 60; r++)
    {
        //ANCHOR check horizontal lines
        dof = 0;
        float disH = 1000000, hx = px, hy = py;
        float aTan = -1 / tan(ra);
        if (ra > PI)
        {
            ry = (((int)py >> 6) << 6) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -64;
            xo = -yo * aTan;
        }
        if (ra < PI)
        {
            ry = (((int)py >> 6) << 6) + 64;
            rx = (py - ry) * aTan + px;
            yo = 64;
            xo = -yo * aTan;
        }
        if (ra == 0 || ra == PI)
        {
            rx = px;
            ry = py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)rx >> 6;
            my = (int)ry >> 6;
            mp = my * mapWidth + mx;
            if (mp > 0 && mp < mapWidth * mapHeight && map[mp] == 1)
            {
                hx = rx;
                hy = ry;
                disH = dist(px, py, hx, hy, ra);
                dof = 8;
            }
            else
            {

                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        //ANCHOR check vertical lines
        dof = 0;
        float disV = 1000000, vx = px, vy = py;
        float nTan = -tan(ra);
        if (ra > P2 && ra < P3)
        {
            rx = (((int)px >> 6) << 6) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -64;
            yo = -xo * nTan;
        }
        if (ra < P2 || ra > P3)
        {
            rx = (((int)px >> 6) << 6) + 64;
            ry = (px - rx) * nTan + py;
            xo = 64;
            yo = -xo * nTan;
        }
        if (ra == 0 || ra == PI)
        {
            rx = px;
            ry = py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)rx >> 6;
            my = (int)ry >> 6;
            mp = my * mapWidth + mx;
            if (mp > 0 && mp < mapWidth * mapHeight && map[mp] == 1)
            {
                vx = rx;
                vy = ry;
                disV = dist(px, py, vx, vy, ra);
                dof = 8;
            }
            else
            {

                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        //ANCHOR calc distance
        int col = 0x00000000;
        if (disH < disV)
        {
            rx = hx;
            ry = hy;
            distT = disH;
            col = 0xed3737ff;
        }
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            distT = disV;
            col = 0xbf2146ff;
        }
        // DrawCircle(vx, vy, 2, GREEN);
        // DrawCircle(hx, hy, 2, RED);
        DrawLine(px, py, rx, ry, YELLOW);

        //ANCHOR draw walls;
        float ca = pa - ra;
        if (ca < 0)
        {
            ca += 2 * PI;
        }
        if (ca > 2 * PI)
        {
            ca -= 2 * PI;
        }
        distT = distT * cos(ca);
        float lineH = (cellSize * 320) / distT;
        if (lineH > 320)
        {
            lineH = 320;
        }
        float lineO = 200 - lineH / 2;

        Vector2 start = {
            (int)r * 8 + 530, lineO};
        Vector2 end = {
            (int)r * 8 + 530, lineH + lineO};

        DrawLineEx(start, end, 8, GetColor(col));

        ra += DR;
        if (ra < 0)
        {
            ra += 2 * PI;
        }
        if (ra > 2 * PI)
        {
            ra -= 2 * PI;
        }
    }
}

//ANCHOR Draw map
void DrawMap()
{
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            if (map[y * mapWidth + x] == 1)
            {
                DrawRectangle(x * cellSize, y * cellSize, cellSize - 1, cellSize - 1, WHITE);
            }
        }
    }
}
