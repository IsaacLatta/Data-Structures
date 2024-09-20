#include "queue.h"

#define NUM_PRODUCERS 1
#define NUM_CONSUMERS 10

void* producer(void* arg)
{
    queue_t* queue = (queue_t*)arg;
    for(int i = 0; i < 100; i ++)
    {
        int* num = (int*)malloc(sizeof(int));
        *num = i;
        printf("Producer:%ld pushing %p:%d\n", pthread_self(),num, *num);
        queue_push(queue, (void*)num);
    }
    printf("Producer:%ld finished\nFreeing queue\n");
    queue_destroy(queue);
    return NULL;
}

void* consumer(void* arg)
{
    queue_t* queue = (queue_t*)arg;
    printf("Consumer:%ld starting ...\n", pthread_self());
    while(1)
    {
        int* i = (int*)queue_pop(queue);
        if(i == NULL && queue->close)
        {
            printf("Queue is closing, consumer:%ld exiting ...\n", pthread_self());
            return NULL;
        }
        printf("Consumer:%ld, popped %p:%d\n", pthread_self(), i, *i);
        free(i);
    }
}

int multi_threaded_test()
{
    queue_t* queue = queue_create();
    pthread_t consumers[NUM_CONSUMERS];
    pthread_t producer_id;
    for(int i =0; i < NUM_CONSUMERS; i++)
    {
        pthread_create(&consumers[i], NULL, consumer, (void*)queue);
    }
    printf("Consumers launched!\n");
    pthread_create(&producer_id, NULL, producer,(void*)queue);
    printf("Producer launched!\nWaiting for producer...\n");
    pthread_join(producer_id, NULL);
    printf("Producer joined\n");
    
    for(int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }
    printf("Consumers joined!\n Multi threaded(single producer test) successfull, exiting gracefully\n");
    return 0;
}

int single_threaded_test()
{
    printf("Creating queue\n");
    queue_t* queue = queue_create();
    int* a = (int*)malloc(sizeof(int));
    int* b;
    *a = 5;
    printf("Pushing to queue %p:%d\n", a, *a);
    queue_push(queue, (void*)a);
    b = (int*)queue_pop(queue);
    printf("Popped from queue %p:%d\n", b, *b);
    printf("Freeing queue ...\n");
    queue_destroy(queue);
    free(a);
    printf("Queue freed, single threaded test successful\n");
    return 0;
}

int main()
{   
    return multi_threaded_test();
}