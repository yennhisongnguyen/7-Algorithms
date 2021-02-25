#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

static int seed = -1;

int randNum()
{
    if(seed != 0)
    {
        seed = 0;
        srand(0);
    }
    return rand();
}