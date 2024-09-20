#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep()

#define NUM_THREADS 4
#define NUM_TASKS 10

void task_function(void* arg)
{
    threadpool_args_t* args = (threadpool_args_t*)arg;
    int* task_num = args->arg1;
    printf("Thread %ld executing task %d\n", pthread_self(), *task_num);
    // Simulate some work
    sleep(3);
}

int threadpool_test()
{
    // Create the threadpool
    threadpool_t* pool = threadpool_create(NUM_THREADS);
    if(pool == NULL)
    {
        printf("Failed to create threadpool\n");
        return -1;
    }

    printf("Adding tasks...\n");
    // Push tasks to the threadpool
    for(int i = 0; i < NUM_TASKS; i++)
    {
        int* task_num = (int*)malloc(sizeof(int));
        *task_num = i;
        if(threadpool_push(pool, task_function, task_num, NULL, NULL) != 0)
        {
            printf("Failed to push task %d to threadpool\n", i);
            free(task_num);  // Free the memory if task pushing fails
        }
    }

    // Allow some time for tasks to be processed
    sleep(2);

    // Destroy the threadpool
    printf("Destroying the threadpool...\n");
    threadpool_destroy(pool);
    printf("Threadpool destroyed, all tasks should be complete.\n");

    return 0;
}

int main()
{
    return threadpool_test();
}
