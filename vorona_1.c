#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000000000

unsigned char mas[N];

int main() 
{
    clock_t start = clock();
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
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%d\n",count);
    printf("\nThe time of work: %f seconds\n", seconds);
}

