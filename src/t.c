#include "../include/raylib.h"
#include <stdio.h>

int main(void){

    const int sc = 320;
    int c = 20;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(sc, sc, "tet");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        int sx = GetScreenWidth()/20;
        int sy = GetScreenHeight()/20;

        

        BeginDrawing();
            ClearBackground(RED);

            for(int y = 0; y<=c; y++){
                for(int x = 0; x <= c; x++){
                    printf("x: %i, y: %i \n", sx, sy);
                    printf("sx: %i, sy: %i \n", GetScreenHeight(), GetScreenHeight());
                    DrawRectangle(x * sx, y * sy, sx-1, sy-1, GREEN);
                }
            }

        EndDrawing();
    }
}