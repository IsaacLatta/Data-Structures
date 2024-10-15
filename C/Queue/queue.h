#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct 
{
    struct _node_t* front;
    struct _node_t* back;
    int close;
    int size;
} queue_t;

queue_t* queue_create();
void queue_push(queue_t* queue, void* data); 
void* queue_pop(queue_t* queue); 
void queue_destroy(queue_t* queue);
int queue_size(queue_t* queue);
#endif 