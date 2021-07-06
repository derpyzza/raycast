#include <stdio.h>
#include <math.h>



typedef struct Vector2
{
    float x;
    float y;
}Vector2;

float Vec2Rad(Vector2 v);

int main (void){
    Vector2 angle = {-1, 1};

    float a = Vec2Rad(angle);

    printf("%f \n", a);
}

float Vec2Rad(Vector2 v)
{
    //tan(angle) = vy/vx
    //angle = atan(vy/vx)
    float angle = atan(v.y / v.x);

    return angle;
}