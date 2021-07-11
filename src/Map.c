#include "../include/raylib.h"
#include "map.h"


int cc = 1;
int mapHeight = 8;
int mapWidth = 8;
int cellSize = 64;
int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1};


void DrawMap(int width, int height, int size)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y * mapWidth + x] == 1)
            {
                DrawRectangle(x * size, y * size, size - cc, size - cc, WHITE);
            }
            else if (map[y * mapWidth + x] == 0)
            {
                DrawRectangle(x * size, y * size, size - cc, size - cc, BLACK);
            }
        }
    }
}

