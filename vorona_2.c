#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define N 1000000000  
#define M 4        

unsigned char mas[N];
int count[M];      

typedef struct 
{
    int thread_id; 
} task;

DWORD __stdcall f(void* arg)
 {
    task* t = (task*)arg;
    int id = t->thread_id;
    int local_ans = 0;
    
    for (int i = id * 2; i < N; i += M * 2) 
    {
        for (int j = 0; j < 2 && (i + j) < N; j++) 
        {
            int idx = i + j;
            int left;
            if (idx == 0) 
            {
                left = -1; 
            } 
            else 
            {
                left = mas[idx - 1];
            }
            int right;
            if (idx == N - 1) 
            {
                right = -1;
            } 
            else 
            {
                right = mas[idx + 1];
            }
            if (mas[idx] > left && mas[idx] > mas[idx + 1]) 
            {
                local_ans++;
            }
        }
    }
    count[id] = local_ans;
}

int main() 
{
    clock_t start = clock();
    int seed = 123, sum;
    srand(seed);
    for (int i = 0; i < N; i++) 
    {
        mas[i] = rand() & 0xff;
    }

    HANDLE th[M];
    task params[M];

    for (int i = 0; i < M; i++) 
    {
        params[i].thread_id = i;
        th[i] = CreateThread(NULL, 0, f, &params[i], 0, NULL);
    }

    WaitForMultipleObjects(M, th, TRUE, INFINITE);
    for (int i = 0; i < M; i++) 
    {
        CloseHandle(th[i]);
    }
    
    for (int i = 0; i < M; i++) 
    {
        printf("%d\t", count[i]);
        sum += count[i];
    }
    printf("%d\n", sum);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time of work: %f seconds\n", seconds);
}
