#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define N 1000000000  
#define M 4        

unsigned char mas[N];
int count[M];      
pthread_t threads[M];
int thread_args[M];
int rc;

typedef struct 
{
    int thread_id; 
} task;

void *f(void* arg) 
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
            if (mas[idx] > left && mas[idx] > right) 
            {
                local_ans++;
            }
        }
    }
    count[id] = local_ans;
}


int main() 
{
    int seed = 123, sum = 0;
    srand(seed);
    for (int i = 0; i < N; i++) {
        mas[i] = rand() & 0xff;
    }

    task params[M];

    for (int i = 0; i < M; i++) {
        params[i].thread_id = i;
        rc = pthread_create(&threads[i], NULL, f, (void *)&params[i]);
        assert(0 == rc);
    }

    for (int i = 0; i < M; i++) {
        rc = pthread_join(threads[i], NULL);
        assert(0 == rc);
    }
    
    for (int i = 0; i < M; i++) {
        printf("%d\t", count[i]);
        sum += count[i];
    }

    printf("%d\n", sum);
}
