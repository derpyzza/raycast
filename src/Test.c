#include <stdio.h>

struct Test
{
    /* data */
    int a;
};
int count;

struct Test array[10];

int main (void){

    for (int i = 0; i < 10; i++)
    {
        /* code */
        array[i].a = count;
        count++;
        printf("%i \n", array[i].a);
    }
    

}