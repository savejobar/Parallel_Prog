#include <stdio.h>
#include <stdlib.h>

#define N 1000000000

unsigned char mas[N];

int main() 
{
    int count = 0, seed = 123;
    srand(seed);
    for (int i = 0; i < 1000000000; i++)
    {
        mas[i] = rand() & 0xff;
    }
    if (mas[0] > mas[1])
    {
        count++;
    }
    if (mas[1000000000-1] > mas[1000000000-2])
    {
        count++;
    }
    for (int i = 1; i < 1000000000-1; i++)
    {
        if ((mas[i] > mas[i-1]) && (mas[i] > mas[i+1]))
        {
            count++;
        }
    }
    printf("%d\n",count);
}

